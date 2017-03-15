library(MASS)
library(ggplot2)

number = 1000
p_value = 0.6

size = 5
alpha = 0.5
shape = 20
col = "black"

cov_matrix = matrix(c(s1^2, s1*s2*p_value, s2*s1*p_value, s2^2), 2)

s1 = 2
s2 = 2

bivn <- mvrnorm(number / 2, 
                mu = c(0, 0), 
                Sigma = cov_matrix)

bivn.kde <- kde2d(bivn[,1], bivn[,2], n = 50)

data_frame <- data.frame(bivn)

p <- ggplot(data_frame, aes(bivn[,1], bivn[,2]))p
p <- p + geom_point(size = size, shape = shape, col = col, alpha = alpha)
p <- p + theme(axis.title = element_blank())

print(p)
