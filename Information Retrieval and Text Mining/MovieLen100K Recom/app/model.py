import torch


class RecManModel(torch.nn.Module):
    def __init__(self,
                 usr_num:int,
                 item_num:int,
                 emb_usr_size:int,
                 emb_item_size:int,
                 usr_feature_dim:int,
                 item_feature_dim:int,
                 feature_hidden_size:int,
                 interact_hidden_size:int):
        '''
        usr_num 和 item_num 为对应用户和物品的总数
        emb_size设定用户和物品的隐变量维度
        feature_dim 为对应用户和物品的特征维度 处理后拼接
        feature_hidden_size 为输入特征映射的维度
        interact_hidden_size 为原来交互时特征维度
        '''
        super(RecManModel,self).__init__()
        self.usr_num = usr_num
        self.item_num = item_num
        self.emb_usr_size = emb_usr_size
        self.emb_item_size = emb_item_size
        self.usr_feature_dim = usr_feature_dim
        self.item_feature_dim = item_feature_dim
        self.feature_hidden_size = feature_hidden_size
        self.interact_hidden_size = interact_hidden_size
            
        self.UserEmbeddingLayer = torch.nn.Embedding(num_embeddings=self.usr_num,
                                                     embedding_dim=self.emb_usr_size)
        self.ItemEmbeddingLayer = torch.nn.Embedding(num_embeddings=self.item_num,
                                                     embedding_dim=self.emb_item_size)
        
        self.UserFeatureLayer1 = torch.nn.Linear(in_features=self.emb_usr_size,
                                                out_features=self.interact_hidden_size)
        self.ItemFeatureLayer1 = torch.nn.Linear(in_features=self.emb_item_size,
                                               out_features=self.interact_hidden_size)
        self.UserFeatureLayer2 = torch.nn.Linear(in_features=self.interact_hidden_size,
                                                out_features=self.interact_hidden_size)
        self.ItemFeatureLayer2 = torch.nn.Linear(in_features=self.interact_hidden_size,
                                               out_features=self.interact_hidden_size)
        self.UserFeatureLayer3 = torch.nn.Linear(in_features=self.interact_hidden_size,
                                                out_features=self.interact_hidden_size)
        self.ItemFeatureLayer3 = torch.nn.Linear(in_features=self.interact_hidden_size,
                                               out_features=self.interact_hidden_size)
        
        self.UserMannualFeatureLayer = torch.nn.Linear(in_features=self.usr_feature_dim,
                                                       out_features=self.feature_hidden_size)
        self.ItemMannualFeatureLayer = torch.nn.Linear(in_features=self.item_feature_dim,
                                                       out_features=self.feature_hidden_size)

        self.Dropout1 = torch.nn.Dropout(p=0.5)
        self.Dropout2 = torch.nn.Dropout(p=0.4)
        self.Dropout3 = torch.nn.Dropout(p=0.3)
        
        
    def forward(self,uid_batch,iid_batch,u_man_feature_batch,i_man_feature_batch):
        '''输入一个batch的usr和item进行交互
        '''
        if not torch.is_tensor(uid_batch):
            u_batch_tensor = torch.tensor(uid_batch)
        else:
            u_batch_tensor = uid_batch
        if not torch.is_tensor(iid_batch):
            i_batch_tensor = torch.tensor(iid_batch)
        else:
            i_batch_tensor = iid_batch
        
        if not torch.is_tensor(u_man_feature_batch):
            u_man_feature_batch = torch.tensor(u_man_feature_batch)
        if not torch.is_tensor(i_man_feature_batch):
            i_man_feature_batch = torch.tensor(i_man_feature_batch)

        # 数据类型转换
        u_man_feature_batch = u_man_feature_batch.to(torch.float)
        i_man_feature_batch = i_man_feature_batch.to(torch.float)
        
        # 嵌入 向量化
        
        u_emb_tensor = self.UserEmbeddingLayer(u_batch_tensor)
        i_emb_tensor = self.ItemEmbeddingLayer(i_batch_tensor)
        
        # 特征抽取 和 非线性化
        u_feature = self.UserFeatureLayer1(u_emb_tensor)
        i_feature = self.ItemFeatureLayer1(i_emb_tensor)

        u_feature = self.Dropout1(u_feature)
        i_feature = self.Dropout1(i_feature)
        
        u_feature = torch.relu(u_feature)
        i_feature = torch.relu(i_feature)

        u_feature = self.UserFeatureLayer2(u_feature)
        i_feature = self.ItemFeatureLayer2(i_feature)

        u_feature = self.Dropout2(u_feature)
        i_feature = self.Dropout2(i_feature)
        
        u_feature = torch.relu(u_feature)
        i_feature = torch.relu(i_feature)

        u_feature = self.UserFeatureLayer3(u_feature)
        i_feature = self.ItemFeatureLayer3(i_feature)

        u_feature = self.Dropout3(u_feature)
        i_feature = self.Dropout3(i_feature)
        
        u_feature = torch.relu(u_feature)
        i_feature = torch.relu(i_feature)
        
        # 外部特征映射
        
        u_mannual_feature = self.UserMannualFeatureLayer(u_man_feature_batch)
        i_mannual_feature = self.ItemMannualFeatureLayer(i_man_feature_batch)
        
        u_mannual_feature = torch.relu(u_mannual_feature)
        i_mannual_feature = torch.relu(i_mannual_feature)
        
        # 隐式显式特征拼接
        u_final_feature = torch.cat([u_feature,u_mannual_feature],dim=1)
        i_final_feature = torch.cat([i_feature,i_mannual_feature],dim=1)
        
        batch_size = u_feature.shape[0]
        interact_hidden_size = self.feature_hidden_size + self.interact_hidden_size
        u_final_feature = u_final_feature.reshape(batch_size,1,interact_hidden_size)
        i_final_feature = i_final_feature.reshape(batch_size,interact_hidden_size,1)
        
        output = torch.bmm(u_final_feature,i_final_feature)
        output = torch.squeeze(output)

        return output