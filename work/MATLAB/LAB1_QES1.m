function LAB1_QES1(n)

    for i = 1:n
    out = factorial(i);
    value = sqrt(2*pi*i)*(i/(exp(1))).^i;
    
    abs_err = abs(out - value);
    rel_err = (abs(out - value))/out;
    
    disp('ABS ERROR : ')
    disp(abs_err)
    disp('REL ERROR : ')
    disp(rel_err)
    end
end
