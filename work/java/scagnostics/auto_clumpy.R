library(ggplot2)
library(scagnostics)

if(0)
{
    root <- "../../"

    originName <- "rays_100_47__picture_0_rate_0.01"

    inputCSV <- paste(root, 
                      "/java/"
                      , sep = "")
    inputCSV <- paste(inputCSV, "/scagnostics/", sep = "")
    inputCSV <- paste(inputCSV, 
                      "rays_100_47__picture_0_rate_0.01"
                      ,".csv"
                      , sep = "")

    outputName <- paste(originName, "_clumpy", ".png", sep = '')
}

inputCSV <- paste(directory, originName, ".csv", sep = "")
outputName <- paste(outputDirectory, originName, ".png", sep = "")
addtionInfo = "./clumpy.csv"

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
colSeq = c("green" , "purple")

point_size <- 3.5
alpha <- 0.55
shape <- 20

col_edge <- "green"
col_runt <- "purple"

size = 3

width <- 320
height <- 320

lwdClumpy <- 2
axes <- FALSE

xlab <- ""
ylab <- ""

colClumpy <- "purple"

cex <- 1
pch <- 20

data <- read.csv(inputCSV, head = FALSE)

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

addtionPoint <- read.csv(addtionInfo, head = FALSE, sep = ',')

row_1 <- addtionPoint[[1]]
row_2 <- addtionPoint[[2]]

row_3 <- addtionPoint[[3]]
row_4 <- addtionPoint[[4]]

data_frame <- data.frame(x, y)

# p <- ggplot(data_frame, aes(x, y))
# p <- p + geom_point(size = point_size, shape = shape, col = col, alpha = alpha)
# p <- p + theme(axis.text.y = element_blank(), axis.text.x = element_blank())
# p <- p + theme(axis.title = element_blank())

png(outputName, width = width, height = height)

plot(data_frame, pch = pch, col = col, cex = cex, axes = axes, xlab = xlab , ylab = ylab, asp = 1)

if(1)
{

    edge_start_x <- get_real_value(mean_x, max_x, min_x, row_1[1])
    edge_start_y <- get_real_value(mean_y, max_y, min_y, row_2[1])

    edge_end_x <- get_real_value(mean_x, max_x, min_x, row_1[2])
    edge_end_y <- get_real_value(mean_y, max_y, min_y, row_2[2])

    segments(edge_start_x, edge_start_y, edge_end_x, edge_end_y, col = col_edge, lwd = size)

    runt_start_x <- get_real_value(mean_x, max_x, min_x, row_3[1])
    runt_start_y <- get_real_value(mean_y, max_y, min_y, row_4[1])

    runt_end_x <- get_real_value(mean_x, max_x, min_x, row_3[2])
    runt_end_y <- get_real_value(mean_y, max_y, min_y, row_4[2])

    segments(runt_start_x, runt_start_y, runt_end_x, runt_end_y, col = col_runt, lwd = size)
}

dev.off()
