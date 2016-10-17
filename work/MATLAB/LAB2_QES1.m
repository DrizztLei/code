function LAB2_QES1(n)
    for i=1:n
    out = (1 + 1/i) ^ i
    disp('DETAL FOR : ')
    disp(out - exp(1))
    end
end