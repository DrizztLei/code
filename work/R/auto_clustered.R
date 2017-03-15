library(ggplot2)

triangle_length = 20

X1 = -triangle_length / 2
Y1 = 0
Z1 = 0

X2 = triangle_length / 2
Y2 = 0
Z2 = 0

X3 = 0
Y3 = triangle_length / 2 * sqrt(3)
Z3 = 0

size = 5
alpha = 0.5
shape = 20

col = "black"

number = 1000

inner_radio = 3
outer_radio = 3

r1 = (runif(number) * (outer_radio ^ 3 - inner_radio ^ 3) + inner_radio ^ 3) * 1/3
phi1 = acos(runif(number, -1, 1));
th1 = 2 * pi * runif(number)

x1 = r1 * sin(phi1) * sin(th1) + X1
y1 = r1 * sin(phi1) * cos(th1) + Y1
z1 = r1 * cos(phi1) + Z1

r2 = (runif(number) * (outer_radio ^ 3 - inner_radio ^ 3) + inner_radio ^ 3) * 1/3
phi2 = acos(runif(number, -1, 1));
th2 = 2 * pi * runif(number)

x2 = r2 * sin(phi2) * sin(th2) + X2
y2 = r2 * sin(phi2) * cos(th2) + Y2
z2 = r2 * cos(phi2) + Z2

r3 = (runif(number) * (outer_radio ^ 3 - inner_radio ^ 3) + inner_radio ^ 3) * 1/3
phi3 = acos(runif(number, -1, 1));
th3 = 2 * pi * runif(number)

x3 = r3 * sin(phi3) * sin(th3) + X3
y3 = r3 * sin(phi3) * cos(th3) + Y3
z3 = r3 * cos(phi3) + Z3

x <- c(x1, x2, x3)
y <- c(y1, y2, y3)
z <- c(z1, z2, z3)


data_frame <- data.frame(x, y)

p <- ggplot(data_frame, aes(x, y))
p <- p + geom_point(size = size, shape = shape, col = col, alpha = alpha)
p <- p + theme(axis.title = element_blank())

print(p)