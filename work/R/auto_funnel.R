library(compositions)

number <- 1000

size = 5
alpha = 0.5
shape = 20

col = "black"

s1 = 4
s2 = 5

std_1 <- sqrt(s1)
std_2 <- sqrt(s2)

mean_1 = 5
mean_2 = 5

p_value <- 0.6

p_value <- log((p_value) * sqrt((exp(s1)-1)*(exp(s2)-1)) + 1) / (std_1 * std_2)

cov_matrix = matrix(c(s1, std_1 * std_2 * p_value, std_1 * std_2 * p_value, s2), 2)

frame <- mvrnorm(number, mu = c(mean_1, mean_2), Sigma = cov_matrix)

x <- frame[, 1]
y <- frame[, 2]

x <- exp(x)
y <- exp(y)

data_frame <- data.frame(x, y)

p <- ggplot(data_frame, aes(x, y))

p <- p + geom_point(size = size, shape = shape, col = col, alpha = alpha)
p <- p + theme(axis.title = element_blank())
p <- p + theme(axis.text = element_blank())

print(p)
print(cor(x, y))

out <- (exp(p_value * std_1 * std_2)- 1) / sqrt(((exp(s1)-1)*(exp(s2)-1)))

print(out)