library(ggplot2)

number = 1000
mean = 10
rate = 1 / mean
range = 0.5
size = 5
shape = 20
alpha = 0.65
shape = 20

col = "black"

x <- rexp(n = number, rate)
y <- rexp(n = number, rate)

x <- x + runif(length(x), -range, range)
y <- y + runif(length(y), -range, range)

data_frame <- data.frame(x, y)
  
p <- ggplot(data_frame, aes(x, y))

p <- p + geom_point(size = size, shape = shape, col=col, alpha = alpha)
p <- p + theme(axis.title = element_blank())

print(p)