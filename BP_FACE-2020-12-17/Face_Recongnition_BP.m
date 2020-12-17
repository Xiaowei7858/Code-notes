function Face_Recongnition_BP %����BP�����������ʶ��
clc %���������
global base net %����ȫ�ֱ���������test.m��������
%% ��һ�����������ݣ�PCA����
all_samples = []; %���屣������ѵ��ͼ�����������
for i = 1:40
    for j = 1:5  %����40*5��ѵ��ͼ��
        a = imread(strcat('.\ORL\s',num2str(i),'\',num2str(j),'.bmp')); %num2str---number to string
        b = a(1:112*92);
        b = double(b); %bΪ�������� 1*N��N=112*92����ȡ˳��Ϊ���к��У����ϵ��£�������
        all_samples = [all_samples;b]; %�γ�M*N�ľ�������ÿһ�����ݴ���һ��ͼƬ������MΪ40
    end
end

%���Э�������
mean_sample = mean(all_samples); %ƽ��ͼƬ��1*N
for i = 1:200
    xmean(i,:) = all_samples(i,:) - mean_sample; %xmean��һ��M*N������ÿһ�б��桰ÿ����Ƭ������-ƽ��ͼƬ��
end

%�������б���ֵ�ͱ�������
sigma = xmean*xmean';
[v,d] = eig(sigma); 

%����ֵ�Ӵ�С����
d1 = diag(d); %�������������ԽǾ�����������Ԫ��Ϊ�Խ�Ԫ��
[d2,index1] = sort(d1); %����������
cols = size(v,2); %�����������������
for i = 1:cols
    vsort(:,i) = v(:, index1(cols - i + 1)); %vsort��һ��M*col�׾��󣬱�����ǰ��������е���������,ÿһ�й���һ����������
    dsort(i) = d1(index1(cols - i + 1)); %dsort������ǰ��������е�����ֵ����һά������
end %�����������

%ѡ��90%����������ֵ
dsum = sum(dsort);
dsum_extract = 0;
p = 0;
while(dsum_extract/dsum < 0.90)
    p = p + 1;
    dsum_extract = sum(dsort(1:p));
end

%�����������γɵ�����ϵ
i = 1;
while(i <= p && dsort(i) > 0)
    base(:,i) = dsort(i)^(-1/2) * xmean' * vsort(:,i); %baseΪN*p���󣬳���dsort(i)^(1/2)�Ƕ�����ͼ��ı�׼��
    i = i + 1;
end

%��ѵ������������ϵ�Ͻ���ͶӰ���õ�һ��M*p����all_coor
all_coor = all_samples * base;

%% �ڶ���������BP������
%����ѵ��BP�����������P
P = mapminmax(all_coor);%��һ��---��ֹ����ʱ������ʱ����С���Ӷ����Ч��
%����Ŀ�����ʸ��T
T = zeros(200,40); 
for i = 1:40
    for j = 1:5
        T((i - 1)*5 + j,i) = 1;
    end
end

%����ѵ������˳��
k = p;
gx2(:,1:k)=P;
gx2(:,(k+1):(k+40))=T;
xd=gx2(randperm(numel(gx2)/(k+40)),:);
gx=xd(:,1:k);d=xd(:,(k+1):(k+40));
P=gx';
T=d';

%����BP������
[R,Q]=size(P);
[S2,Q]=size(T);
net=newff(minmax(P),T,[fix(sqrt(R*S2))],{'logsig','purelin'},'traingdx');

%ѵ��������
net.trainparam.epochs = 20000;  %ѭ����������
net.trainparam.goal = 0.001;  %��������������������ٵ�Ŀ�귶Χ<0.001
net.divideFcn = '';  %���е�����������ѵ��
net = train(net,P,T);

%����BP������
Y = sim(net,P);

%% ������������BP�����粢������ʶ����
s = 0;
for i = 1:40
    for j = 6:10  %����40*5������ͼ��
        a = imread(strcat('.\ORL\s',num2str(i),'\',num2str(j),'.bmp'));
        b = a(1:10304);
        b = double(b);
        tcoor = b * base; %�������꣬1*p����
        X = mapminmax(tcoor); %��һ��---��ֹ����ʱ������ʱ����С���Ӷ����Ч��
        Z = sim(net,X');
        [zi,index2] = max(Z);
        if index2 == i
            s = s + 1;
        else
            i         %���ʶ�������Ǹ���i
            j         %���ʶ����������ͼƬj
            index2    %�����ʶ��ɵ��Ǹ���
        end
    end
end
        
%����ʶ����
accuracy = s/Q
