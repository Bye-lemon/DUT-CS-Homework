import pickle
import os
import re
import copy
from collections import Counter

import pandas as pd
import numpy as np

import matplotlib.pyplot as plt

import seaborn as sns

import torch
from torch.utils.data import DataLoader
import torch.optim.lr_scheduler as lr_scheduler
import torch.optim

from sklearn.metrics import mean_squared_error

from model import RecManModel
from loader import MLManDataSet

# Define
LOG = lambda x: print(x)
BATCH_SIZE = 1024
MODEM = "TRAIN+TEST"
DEBUG = False
FLOD = 5
EPOCHS = 5
LEARNING_RATE = 0.05

# Load Device
DEVICE = 'cuda:0' if torch.cuda.is_available() else 'cpu'
LOG(f"[Device]   Using {DEVICE}")

# Load Data
data_df = pd.read_pickle(r"C:\Users\Bye_l\Downloads\SearchGroupCode-main\Recom_movieLen\data\processed\data_df.pkl")
total_usr = len(set(data_df.usr_id.tolist()))
total_item = len(set(data_df.item_id.tolist()))
usr_feature_df = pd.read_pickle(r"C:\Users\Bye_l\Downloads\SearchGroupCode-main\Recom_movieLen\data\processed\usr_feature_df.pkl")
item_feature_df = pd.read_pickle(r"C:\Users\Bye_l\Downloads\SearchGroupCode-main\Recom_movieLen\data\processed\item_feature_df.pkl")
u_feature_dim = usr_feature_df['features'][0].shape[0]
i_feature_dim = item_feature_df['features'][0].shape[0]

cv_df_lst = []
for i in range(5):
    df_fname = r"C:\Users\Bye_l\Downloads\SearchGroupCode-main\Recom_movieLen\data\processed\cv_{0}_df.pkl".format(i+1)
    df = pd.read_pickle(df_fname)
    cv_df_lst.append(df)

mse_lst = []

for test_idx in range(FLOD):
    model = RecManModel(usr_num=total_usr,item_num=total_item,
                 emb_usr_size=50,emb_item_size=150,
                 usr_feature_dim=u_feature_dim,item_feature_dim=i_feature_dim,
                 feature_hidden_size=100,interact_hidden_size=250)
    model.to(DEVICE)

    optimizer = torch.optim.SGD([
            {'params': model.parameters()},
                    ], lr=LEARNING_RATE,momentum=0.9)

    if "TRAIN" in MODEM:
        model.train()
        for epoch in range(EPOCHS):
            if DEBUG:
                LOG(f"[Trainer]  Start training")
            train_idx_lst = [i for i in range(FLOD) if i != test_idx]
            # 训练过程
            train_df_lst = []
            for train_idx in train_idx_lst:
                df = cv_df_lst[train_idx]
                train_df_lst.append(df[df['type']=='test'])
            train_df = pd.concat(train_df_lst)
            train_dataset = MLManDataSet(train_df,usr_feature_df=usr_feature_df,item_feature_df=item_feature_df)
            train_dataloader = DataLoader(train_dataset,batch_size=BATCH_SIZE)
            
            for num,(uid_batch,iid_batch,usr_feature,item_feature,true_y) in enumerate(train_dataloader):
                optimizer.zero_grad()
                criterion = torch.nn.MSELoss()
                uid_batch,iid_batch,usr_feature,item_feature = map(
                    lambda x: x.to(DEVICE), [uid_batch,iid_batch,usr_feature,item_feature])
                pred_y = model(uid_batch,iid_batch,usr_feature,item_feature)
                true_y = true_y.to(torch.float).to(DEVICE)
                loss = criterion(pred_y,true_y)
                # loss.requires_grad_(True)
                loss.backward()
                if DEBUG:
                    LOG(f"[Trainer]  Epoch:{epoch} Batch:{num} Loss:{loss}")
                optimizer.step()

    if "TEST" in MODEM:
        model.eval()
        df = cv_df_lst[test_idx]
        test_df = df[df['type']=='test']

        test_dataset = MLManDataSet(test_df,usr_feature_df=usr_feature_df,item_feature_df=item_feature_df)
        test_dataloader = DataLoader(test_dataset,batch_size=BATCH_SIZE)

        temp_mse_lst = []
        # 分batch进行MSE计算 最后平均
        for num,(test_uid_batch,test_iid_batch,test_usr_feature,test_item_feature,test_true_y) in enumerate(train_dataloader):
            test_uid_batch,test_iid_batch,test_usr_feature,test_item_feature = map(
                        lambda x: x.to(DEVICE), [test_uid_batch,test_iid_batch,test_usr_feature,test_item_feature])
            test_pred_y = model(test_uid_batch,test_iid_batch,test_usr_feature,test_item_feature)
            test_pred_y = test_pred_y.cpu().detach().numpy()
            
            mse_batch = mean_squared_error(test_true_y,test_pred_y)
            temp_mse_lst.append(mse_batch)         
        mse = np.average(temp_mse_lst)
        mse_lst.append(mse)
        print(f"MSE on cv_{test_idx}_df:{mse}")

LOG(f"Average MSE:{np.average(mse_lst)}")