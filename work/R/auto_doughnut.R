library(ggplot2)

X = 0
Y = 0

size = 5
alpha = 0.55
shape = 20
col = "black"

number_all = 10000
number_inner = 100
number_outer = 100

inner_radio = 3
outer_radio = 6
width = 1

get_outer_data <- function(number, inner_radio, outer_radio, width)
{
  return_x <- c()
  return_y <- c()
  
  while(TRUE)
  {
   if(length(return_x) == number)
   {
     break
   }
   else
   {
     x <- runif(1, -outer_radio, outer_radio)
     y <- runif(1, -outer_radio, outer_radio)
     
     value <- x * x + y * y
     
     if(value > inner_radio ** 2 && value < outer_radio ** 2)
     {
       return_x <- c(return_x, x)
       return_y <- c(return_y, y)
     }
   }
  }
  return(data.frame(return_x, return_y))   
}

data_frame <- get_outer_data(number_all, inner_radio, outer_radio, width)

p <- ggplot(data_frame, aes(data_frame$return_x, data_frame$return_y))

p <- p + geom_point(size = size, shape = shape, col = col, alpha = alpha)
p <- p + theme(axis.title = element_blank())

print(p)