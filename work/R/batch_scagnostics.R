library("scagnostics")

directory <- "./csv/EUROVIS_new/"
out_direcotry <- "./csv/EUROVIS_new_result/"

filelist <- list.files(directory)
count <- 0

for (filename in filelist)
{
  data <- read.csv(paste(directory, filename, sep = ''), header = FALSE)
  
  out_name <- paste(out_direcotry, filename, sep = '')
  
  print(out_name)
  
  x <- data[[1]]
  y <- data[[2]]
  
  range_x <- max(x) - min(x)
  range_y <- max(y) - min(y)
  
  y <- y * range_x / range_y
  
  data_frame <- data.frame(x, y)
  
  result <- scagnostics(data_frame)
  
  result <- c(result)
 
  print(out_name) 
  
  write.table(result,
              file = out_name,
              append = FALSE, 
              quote = FALSE, 
              sep = ",", 
              col.names = FALSE, 
              row.names = c("Outlying", "Skewed", "Clumpy", "Sparse", "Striated", "Convex", "Skinny", "Stringy", "Monotonic"))
  
}