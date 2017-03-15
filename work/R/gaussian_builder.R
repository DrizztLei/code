x1 <- rnorm(100, mean = 5, sd = 1)
x2 <- rnorm(100, mean = 10, sd = 1)

y1 <- rnorm(100, mean = 5, sd = 1)
y2 <- rnorm(100, mean = 5, sd = 1)

gaussian_data <- data.frame(c(x1, x2), c(y1, y2))

write.csv(gaussian_data, "out.csv")

auto_plot <- function(distanct, mean_value, stddev, number)
{
  x1 <- rnorm(number, mean_value, stddev); 
  x2 <- rnorm(number, mean_value + distanct, stddev); 
  y1 <- rnorm(number, mean_value, stddev); 
  y2 <- rnorm(number, mean_value, stddev); 
  
  plot(c(x1, x2), c(y1, y2), pch=20); 
  frame <- data.frame(c(x1, x2), c(y1, y2)); 
  scagnostics(frame)
}