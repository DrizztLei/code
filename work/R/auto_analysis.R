file_name <- 'C:\\Users\\Elvis Lei\\Documents\\data\\Banking\\data_dole.csv.asd'
data = read.csv(file = file_name, sep = ',')

library(fmsb)

upper = 1
floor = -1
scope = c(upper, floor)
segmentation = 20

maxmin <- data.frame(
  outlying = scope,
  skewed = scope,
  clumpy = scope,
  sparse = scope, 
  striated = scope,
  convex = scope,
  skinny = scope,
  stringy = scope,
  monotonic = scope
)


start <- 0.1
sample_number <- 19
scagnostics_number <- 9
step <- 0.05

print(file_name)
cat("\n\trange from ", start, " to ", start+step*(sample_number - 1)," by the step ", step,"\n")
aspect_ratio <- seq(start, start + step*(sample_number - 1), step)
feature_name <- c("outlying", "skewed", "clumpy", "sparse", "striated", "convex", "skinny", "stringy", "monotonic")

out <- c()
info_before_threshold <- c()

for(i in c(1:scagnostics_number))
{
  feature <- data[[i]][1:sample_number]
  p_value <- cor(aspect_ratio, feature)
  temp <- rbind(feature_name[i], p_value)
  info_before_threshold <- cbind(info_before_threshold, p_value)
  out <- cbind(out, temp)
}

print(out)

chart <- rbind(maxmin, info_before_threshold[1:length(info_before_threshold)])

start <- 1
before_sample_number <- sample_number
sample_number <- 19
scagnostics_number <- 9
step <- 0.5

cat("\n\trange from ", start, " to ", start+step*(sample_number - 1), " by the step ", step, "\n")
aspect_ratio <- seq(start, start + step*(sample_number - 1), step)
feature_name <- c("outlying", "skewed", "clumpy", "sparse", "striated", "convex", "skinny", "stringy", "monotonic")

out <- c()
info_after_threshold <- c()

for(i in c(1:scagnostics_number))
{
  # feature <- data[[i]][before_sample_number:(before_sample_number+sample_number-1)]
  feature <- data[[i]][before_sample_number:(before_sample_number + sample_number - 1)]
  p_value <- cor(aspect_ratio, feature)
  temp <- rbind(feature_name[i], p_value)
  info_after_threshold <- cbind(info_after_threshold, p_value)
  out <- cbind(out, temp)
}

print(out)

chart <- rbind(chart, info_after_threshold[1:length(info_after_threshold)])

png_file_name <- paste(file_name, ".png", sep = "")

png(filename = png_file_name)
radarchart(chart, seg = segmentation, centerzero = FALSE, axistype = 0)
dev.off()