library(ggplot2)
library(scagnostics)

inputCSV <- paste(directory, originName, ".csv", sep = "")
pngName <- paste(outputDirectory, originName, ".png", sep = "")
diameterInfo <- "./diameter.csv"

width <- 320
height <- 320

lwddiameter <- 2

col = ""

flag <- grep("rate_0.2", originName, value = F)
if(length(flag) != 0)
{
    col = "blue"
}

flag <- grep("rate_0.01", originName, value = F)
if(length(flag) != 0)
{
    col = "black"
}

flag <- grep("rate_0.05", originName, value = F)
if(length(flag) != 0)
{
    col = "red"
}

axes <- FALSE

xlab <- ""
ylab <- ""

coldiameter <- "purple"
colOneDegree <- "gray"
colTwoDegree <- "red"
colOtherDegree <- "black"

cex <- 2
pch <- 20

cexOneDegree = 2
cexTwoDegree = 2

data <- read.csv(inputCSV, head = FALSE)
diameter <- read.csv(diameterInfo, head = FALSE, sep = ',')

x <- data[[1]]
y <- data[[2]]

rx <- max(x) - min(x)
ry <- max(y) - min(y)

y <- y * rx / ry

mean_x <- mean(x)
mean_y <- mean(y)

max_x <- max(x)
min_x <- min(x)

max_y <- max(y)
min_y <- min(y)

get_real_value <-function(mean, max, min, value)
{
    return_value <- (value/1000) * (max - min) + min
}

data_frame <- data.frame(x, y)

diameter_x <- diameter[[1]]
diameter_y <- diameter[[2]]
diameter_label <- diameter[[3]]

one_degree_choose <- diameter_label == 1
two_degree_choose <- diameter_label == 2
other_degree_choose <- diameter_label == 0

png(pngName, width = width, height = height)

plot(diameter_x[one_degree_choose], diameter_y[one_degree_choose], pch = pch, col = colOneDegree, cex = cexOneDegree, axes = axes, xlab = xlab, ylab = ylab, asp = 1)
points(diameter_x[two_degree_choose], diameter_y[two_degree_choose], pch = pch, col = colTwoDegree, cex = cexOneDegree)
points(diameter_x[other_degree_choose], diameter_y[other_degree_choose], pch = pch, col = colOtherDegree, cex = cex)

dev.off()
