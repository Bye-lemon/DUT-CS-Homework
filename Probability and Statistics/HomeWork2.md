# 概率论与数理统计第二次上机作业

*电计1601班 李英平 201685040*

---

**题目：**

1. 模拟产生$1000$个随机变量$X$服从均匀分布$U(5,10)$，进而计算$Y=4X-6$。分别计算$X$和$Y$的均值。
2. 根据由问题$1$产生的数据分别计算$X$和$Y$的方差$D(X)$和$D(Y)$，以及协方差$Cov(X,Y)$。进而计算$X$和$Y$的相关系数$Corr(X,Y)$。
3. 利用问题$1$中所产生的服从均匀分布的随机变量$X$，讨论当$Y=X*exp(2X^{n-1})$, $n$分别取$1,2,3$时，$X$和$Y$的相关系数的变化并作相应解释。

**MATLAB程序：**
```matlab
%第一题
X=unifrnd(5,10,1,1000);
Y=4.*X-6;
Bar_X=mean(X)
Bar_Y=mean(Y)
%第二题
COV_Matrix=cov(X,Y);
D_X=COV_Matrix(1,1)
D_Y=COV_Matrix(2,2)
COV_XY=COV_Matrix(1,2)		
Corr_Matrix=corrcoef(X,Y);
Corr_XY=Corr_Matrix(1,2)
%第三题
for n=1:3
    Y=X.*exp(2.*X.^(n-1));
    Corr_Matrix=corrcoef(X,Y);
    Corr_XY=Corr_Matrix(1,2)
end
```

**输出结果：**
| 变量        | 输出值  |
| :----:   | :----:  |
| $X$均值     |  $7.4442$    |
| $X$方差     |  $2.0056$   |
| $Y$均值     |  $23.7767$  |
| $Y$方差     |  $32.0904$  |
| $X,Y$协方差     |  $8.0226$  |
| $X,Y$相关系数     |  $1$  |
| $X,Y_{(n=1)}$相关系数     |  $1$  |
| $X,Y_{(n=2)}$相关系数     |  $0.6616$  |
| $X,Y_{(n=3)}$相关系数     |  $0.1519$  |

**$X,Y$相关系数减小的原因：**

* $Xe^{2X^{n-1}}$当$n$为$1$时是正比例函数，与$X$线性相关。
* $Xe^{2X^{n-1}}$当$n$为$2,3$时是正比例函数与指数函数的积，$n$越大与正比例函数偏移越大，相关系数越小。

