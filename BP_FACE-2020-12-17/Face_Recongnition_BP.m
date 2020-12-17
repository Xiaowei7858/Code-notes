function Face_Recongnition_BP %基于BP神经网络的人脸识别
clc %清空命令行
global base net %定义全局变量，用于test.m函数测试
%% 第一步，读入数据，PCA处理
all_samples = []; %定义保存所有训练图像的特征矩阵
for i = 1:40
    for j = 1:5  %读入40*5幅训练图像
        a = imread(strcat('.\ORL\s',num2str(i),'\',num2str(j),'.bmp')); %num2str---number to string
        b = a(1:112*92);
        b = double(b); %b为单行向量 1*N，N=112*92，提取顺序为先列后行，从上到下，从左到右
        all_samples = [all_samples;b]; %形成M*N的矩阵，其中每一行数据代表一张图片，其中M为40
    end
end

%求出协方差矩阵
mean_sample = mean(all_samples); %平均图片，1*N
for i = 1:200
    xmean(i,:) = all_samples(i,:) - mean_sample; %xmean是一个M*N矩阵，其每一行保存“每张照片的数据-平均图片”
end

%计算所有本征值和本征向量
sigma = xmean*xmean';
[v,d] = eig(sigma); 

%特征值从大到小排序
d1 = diag(d); %根据向量创建对角矩阵，以向量的元素为对角元素
[d2,index1] = sort(d1); %以升序排序
cols = size(v,2); %特征向量矩阵的列数
for i = 1:cols
    vsort(:,i) = v(:, index1(cols - i + 1)); %vsort是一个M*col阶矩阵，保存的是按降序排列的特征向量,每一列构成一个特征向量
    dsort(i) = d1(index1(cols - i + 1)); %dsort保存的是按降序排列的特征值，是一维行向量
end %降序排列完成

%选择90%的能量特征值
dsum = sum(dsort);
dsum_extract = 0;
p = 0;
while(dsum_extract/dsum < 0.90)
    p = p + 1;
    dsum_extract = sum(dsort(1:p));
end

%计算特征脸形成的坐标系
i = 1;
while(i <= p && dsort(i) > 0)
    base(:,i) = dsort(i)^(-1/2) * xmean' * vsort(:,i); %base为N*p矩阵，除以dsort(i)^(1/2)是对人脸图像的标准化
    i = i + 1;
end

%将训练样本对坐标系上进行投影，得到一个M*p矩阵all_coor
all_coor = all_samples * base;

%% 第二步，创建BP神经网络
%生成训练BP神经网络的输入P
P = mapminmax(all_coor);%归一化---防止数据时而过大时而过小，从而提高效率
%生成目标输出矢量T
T = zeros(200,40); 
for i = 1:40
    for j = 1:5
        T((i - 1)*5 + j,i) = 1;
    end
end

%打乱训练样本顺序
k = p;
gx2(:,1:k)=P;
gx2(:,(k+1):(k+40))=T;
xd=gx2(randperm(numel(gx2)/(k+40)),:);
gx=xd(:,1:k);d=xd(:,(k+1):(k+40));
P=gx';
T=d';

%创建BP神经网络
[R,Q]=size(P);
[S2,Q]=size(T);
net=newff(minmax(P),T,[fix(sqrt(R*S2))],{'logsig','purelin'},'traingdx');

%训练神经网络
net.trainparam.epochs = 20000;  %循环次数上限
net.trainparam.goal = 0.001;  %输出层误差于输入层误差减少到目标范围<0.001
net.divideFcn = '';  %所有的样本都用于训练
net = train(net,P,T);

%仿真BP神经网络
Y = sim(net,P);

%% 第三步，测试BP神经网络并计算其识别率
s = 0;
for i = 1:40
    for j = 6:10  %读入40*5幅测试图像
        a = imread(strcat('.\ORL\s',num2str(i),'\',num2str(j),'.bmp'));
        b = a(1:10304);
        b = double(b);
        tcoor = b * base; %计算坐标，1*p矩阵
        X = mapminmax(tcoor); %归一化---防止数据时而过大时而过小，从而提高效率
        Z = sim(net,X');
        [zi,index2] = max(Z);
        if index2 == i
            s = s + 1;
        else
            i         %输出识别出错的那个人i
            j         %输出识别出错的那张图片j
            index2    %输出误识别成的那个人
        end
    end
end
        
%计算识别率
accuracy = s/Q
