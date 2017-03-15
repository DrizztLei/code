library(ggplot2)

number <- 1000
size = 5
alpha = 0.55
shape = 20
col = "black"

min_x <- 0
max_x <- 1

min_y <- 1
max_y <- 6

x <- runif(number, min_x, max_x)
y <- runif(number, min_y, max_y)

y <- as.integer(y)
y <- y * x

data_frame <- data.frame(x, y)

p <- ggplot(data_frame, aes(x, y))

p <- p + geom_point(size = size, shape = shape, col = col, alpha = alpha)
p <- p + theme(axis.title = element_blank())

print(p)