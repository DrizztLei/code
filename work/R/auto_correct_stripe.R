library(ggplot2)

number <- 100
size = 5
alpha = 0.55
shape = 20
col = "black"

min_x <- 1
max_x <- 5

min_y <- 1
max_y <- 5

x <- runif(number, min_x, max_x + 1)
y <- runif(number, min_y, max_y)

x <- as.integer(x)

data_frame <- data.frame(x, y)

p <- ggplot(data_frame, aes(x, y))

p <- p + geom_point(size = size, shape = shape, col = col, alpha = alpha)
p <- p + theme(axis.title = element_blank())

print(p)