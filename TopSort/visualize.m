clear
load result_14.txt;
A = zeros(5040,1);
for i = 1:size(result_14,1)
    A(result_14(i,1),1)=1;
end
B = zeros(5040,1000);
for i= 1:1000
    B(:,i) = A(:,1);
end
spy(B,'k')
%颜色是cmgk