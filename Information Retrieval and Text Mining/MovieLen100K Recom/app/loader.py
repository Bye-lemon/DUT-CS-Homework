import pandas as pd
import numpy as np

import torch
from torch.utils.data import Dataset
from torch.utils.data import DataLoader
import torch.optim

data_df = pd.read_pickle(r"C:\Users\Bye_l\Downloads\SearchGroupCode-main\Recom_movieLen\data\processed\data_df.pkl")
total_usr = len(set(data_df.usr_id.tolist()))
total_item = len(set(data_df.item_id.tolist()))
usr_feature_df = pd.read_pickle(r"C:\Users\Bye_l\Downloads\SearchGroupCode-main\Recom_movieLen\data\processed\usr_feature_df.pkl")
item_feature_df = pd.read_pickle(r"C:\Users\Bye_l\Downloads\SearchGroupCode-main\Recom_movieLen\data\processed\item_feature_df.pkl")
u_feature_dim = usr_feature_df['features'][0].shape[0]
i_feature_dim = item_feature_df['features'][0].shape[0]

def get_UI_feature(uid,iid,
           usr_feautre_df,
           item_feature_df):
    '''给定用户和物品id进行特征查找 此处id是处理后的id即-1后的id
    '''
    
    u_feature = usr_feature_df.loc[uid,'features']
    u_feature = np.array(u_feature)
    i_feature = item_feature_df.loc[iid,'features']
    i_feature = np.array(i_feature)
    return u_feature,i_feature

class MLManDataSet(Dataset):
    def __init__(self,df,usr_feature_df,item_feature_df):
        '''
        输入df 构造dataset
        输出 样本编号和标注
        '''
        self.df = df.copy()
        self.usr_feature_df = usr_feature_df.copy()
        self.item_feature_df = item_feature_df.copy()
        # 注意 原始数据用户id和物品id从1开始的，但是在embedding过程中是从0算的，因此此处减一
        self.df['usr_id'] = df['usr_id'].apply(lambda x:int(x)-1)
        self.df['item_id'] = df['item_id'].apply(lambda x:int(x)-1)
        self.df['rating'] = df['rating'].apply(lambda x:int(x))
        
    def __len__(self):
        return self.df.shape[0]
    
    def __getitem__(self,idx):
        if torch.is_tensor(idx):
            idx = idx.tolist()
        sample_df = self.df.iloc[idx]
        usr_feature,item_feature = get_UI_feature(sample_df.usr_id,sample_df.item_id,self.usr_feature_df,self.item_feature_df)
        sample = (sample_df.usr_id,sample_df.item_id,usr_feature,item_feature,sample_df.rating)
        return sample
