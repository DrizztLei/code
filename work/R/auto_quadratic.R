library(ggplot2)

X = 0
Y = 0

number = 1000
inner_radio = 3
outer_radio = 5

number = 1000
a = 1
b = 1
c = 1

range = 3
step = 0.001
size = 3
shape = 20
alpha = 0.7
shape = 21
down = -1
up = 1

col = "black"

x <- seq(-range, range, step)

y <- a * x ** 2 + b * x ** 1 + c * x ** 0

y <- y + runif(length(y), down, up)

data_frame <- data.frame(x, y)
  
p <- ggplot(data_frame, aes(x, y))

p <- p + geom_point(size = size, shape = shape, col=col, alpha = alpha)
p <- p + theme(axis.title = element_blank())

print(p)