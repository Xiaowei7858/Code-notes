function test % 测试 Face_Recognition_BP.m 函数中提到的人脸识别

global base net %使用 Face_Recognition_BP.m 函数中定义的全局变量
i = input('输入想测试的那个人的编号（1~40）:');
j = input('输入这个人10张人脸图像中的一张（1~10）:');
a = imread(strcat('.\ORL\s',num2str(i),'\',num2str(j),'.pgm'));
         b = a(1:10304);
         b = double(b);
         tcoor = b * base;           %计算坐标，是1×p阶矩阵
         x = mapminmax(tcoor);       %归一化
z = net(x');
[max_z,index] = max(z);

s = sprintf('这张人脸图像是 %d 号人的\n',index);
disp(s)