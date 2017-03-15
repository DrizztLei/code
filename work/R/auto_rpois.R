library(ggplot2)

auto_rpois <- function(n, lambda = 5)
{
  out_x <- c()
  out_y <- c()
  
  for(i in seq(0, sqrt(n) - 1))
  {
    for(j in seq(0, sqrt(n) - 1))
    {
      number <- rpois(1, lambda = lambda)
      x <- i
      y <- j
      for(k in seq(0, number))
      {
         out_x <- c(out_x, x + runif(1, 0, 1))
         out_y <- c(out_y, y + runif(1, 0, 1))
      }
    }
  }
  
  data_frame <- data.frame(out_x, out_y)
  
  p <- ggplot(data_frame, aes(out_x, out_y))
  p <- p + geom_point(size = 5, shape = 20, col="black", alpha = 0.7)
  # p <- p + theme(axis.text = element_blank())
  p <- p + theme(axis.title = element_blank())
  print(p)
}

auto_rpois(4, 8)