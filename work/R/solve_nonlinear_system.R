args = commandArgs()

from <- as.numeric(args[6])
to <- as.numeric(args[7])

coeff <- args[8: length(args)]
coeff <- as.numeric(coeff)

parameter <- c()

f<-function(x)
{
  value <- 0
  for(i in seq(1:length(coeff)))
  {
    value <- value + x + coeff[i] * x ** i 
  }
  value
}

result <- optimize(f, c(from, to))
print(result)