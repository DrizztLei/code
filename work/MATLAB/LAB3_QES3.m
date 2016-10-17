function [result] = LAB3_QES3(x,y)

[u,y] = LAB3_QES2(x,y);
[n] = size(u);

for j=n:-1:1
    if u(j,j)==0
        break;
    else
        result(j)=y(j)/u(j,j);
    end
    for i=1:j-1
        y(i)=y(i)-u(i,j)*result(j);
    end
end
        