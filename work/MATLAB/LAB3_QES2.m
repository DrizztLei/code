
function [u,y]=LAB3_QES2(a,b)

[l,u] = LAB3_QES1(a);

LENGTH = size(l);

y = zeros(length(b),1);

for j = 1:LENGTH
    y(j) = b(j) / l(j,j);
    
    for i = j+1:LENGTH
        b(i) = b(i) - l(i,j) * y(j);
    end
    
end

