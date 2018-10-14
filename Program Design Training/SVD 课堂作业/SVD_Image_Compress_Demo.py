import numpy as np 
from matplotlib import pyplot as plt
 
def SVDImageCompress(filename,rate):
    original=plt.imread(filename)
    # 提取RGB通道原始数据
    R0=np.array(original[:,:,0])
    G0=np.array(original[:,:,1])
    B0=np.array(original[:,:,2])
	# 各通道进行SVD分解（调用Numpy的线性工具包linalg）
    U_R,Sigma_R,V_R=np.linalg.svd(R0)
    U_G,Sigma_G,V_G=np.linalg.svd(G0)
    U_B,Sigma_B,V_B=np.linalg.svd(B0)
	# 用零矩阵初始化SVD还原后的图像图像
    R1=np.zeros(R0.shape)
    G1=np.zeros(G0.shape)
    B1=np.zeros(B0.shape)
	# 使用SVD分解后的矩阵重建各通道图像
    for i in range(int(rate*len(Sigma_R))+1):
        R1+=Sigma_R[i]*np.dot(U_R[:,i].reshape(-1,1),V_R[i,:].reshape(1,-1))
    for i in range(int(rate*len(Sigma_G))+1):
        G1+=Sigma_G[i]*np.dot(U_G[:,i].reshape(-1,1),V_G[i,:].reshape(1,-1))
    for i in range(int(rate*len(Sigma_B))+1):
        B1+=Sigma_B[i]*np.dot(U_B[:,i].reshape(-1,1),V_B[i,:].reshape(1,-1))
	# 合并RGB通道
    final=np.stack((R1,G1,B1),2)
    final[final>255]=255
    final[final<0]=0
    final=np.rint(final).astype('uint8')
    return final
    
if __name__=='__main__':
    # 测试代码，分别给出0.1，0.3，0.5的压缩率下的结果
    file='test.jpg'
    for rate in [0.1, 0.3, 0.5]:
        plt.imsave("SVD_Out_With_"+str(rate)+".jpg", SVDImageCompress(file, rate))