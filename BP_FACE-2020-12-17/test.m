function test % ���� Face_Recognition_BP.m �������ᵽ������ʶ��

global base net %ʹ�� Face_Recognition_BP.m �����ж����ȫ�ֱ���
i = input('��������Ե��Ǹ��˵ı�ţ�1~40��:');
j = input('���������10������ͼ���е�һ�ţ�1~10��:');
a = imread(strcat('.\ORL\s',num2str(i),'\',num2str(j),'.pgm'));
         b = a(1:10304);
         b = double(b);
         tcoor = b * base;           %�������꣬��1��p�׾���
         x = mapminmax(tcoor);       %��һ��
z = net(x');
[max_z,index] = max(z);

s = sprintf('��������ͼ���� %d ���˵�\n',index);
disp(s)