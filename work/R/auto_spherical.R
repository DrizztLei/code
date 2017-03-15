library(ggplot2)

number = 1000

triangle_length = 20

X1 = -triangle_length / 2
Y1 = 0
Z1 = 0

size = 5
alpha = 0.5
shape = 20

col = "black"


inner_radio = 3
outer_radio = 3

r1 = (runif(number) * (outer_radio ^ 3 - inner_radio ^ 3) + inner_radio ^ 3) * 1/3
phi1 = acos(runif(number, -1, 1));
th1 = 2 * pi * runif(number)

x1 = r1 * sin(phi1) * sin(th1) + X1
y1 = r1 * sin(phi1) * cos(th1) + Y1
z1 = r1 * cos(phi1) + Z1

x <- x1
y <- y1
z <- z1

data_frame <- data.frame(x, y)

p <- ggplot(data_frame, aes(x, y))
p <- p + geom_point(size = size, shape = shape, col = col, alpha = alpha)
p <- p + theme(axis.title = element_blank())

print(p)