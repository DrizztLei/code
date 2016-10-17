function [L , U] = LAB3_QES1(matrix)

shape = size(matrix);

L = zeros(shape);

U = zeros(shape);

for i=1:shape[0];
   L(i,1) = 1;
   U(1,i) = matrix(1,i);
end

    for x=2:shape[0];
        for y=x:shape[0];
            U(x,y) = matrix(x,y) - sumTypeA(L , U , x , y , shape(1));
            L(y,x) = (matrix(x,y) - sumTypeB(L , U , x , y , shape(1))) / U(x,x);
        end
    end
end

function valueA=sumTypeA(L , U , x , y , shape)
    valueA = 0.0;
    for i=1:shape;
        valueA = valueA + L(x,i) * U(i,y);
    end
end

function valueB=sumTypeB(L , U , x , y , shape)
    valueB = 0.0;
    for i=1:shape;
        valueB = valueB + L(y,i)*U(i,x);
    end
end