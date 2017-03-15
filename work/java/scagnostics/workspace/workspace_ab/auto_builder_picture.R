library(ggplot2)
library(methods)
library(rJava)
library(scagnostics)

args <- commandArgs()

directory <- args[6]
originName <- args[7]
outputDirectory <- args[8]

backupDirectory <- outputDirectory

fileName <- paste(directory, "/", originName, ".csv", sep = "")

print(fileName)

info <- read.csv(fileName, head = FALSE)

x <- info[[1]]
y <- info[[2]]

max_x <- max(x)
min_x <- min(x)

max_y <- max(y)
min_y <- min(y)

y <- y * (max_x - min_x) / (max_y - min_y)

result <- scagnostics(data.frame(x, y))

# print(outputDirectory)
# print(originName)

outputDirectory <- gsub("NEW_DELETE_POING/new_delete_point", "NEW_MEASURE/Clumpy", backupDirectory)
# print(outputDirectory)
source("./auto_clumpy.R")

outputDirectory <- gsub("NEW_DELETE_POING/new_delete_point", "NEW_MEASURE/Convex", backupDirectory)
# print(outputDirectory)
# source("./auto_convex.R")

outputDirectory <- gsub("NEW_DELETE_POING/new_delete_point", "NEW_MEASURE/Skewed", backupDirectory)
# print(outputDirectory)
# source("./auto_skewed.R")

outputDirectory <- gsub("NEW_DELETE_POING/new_delete_point", "NEW_MEASURE/Outlying_MST", backupDirectory)
# print(outputDirectory)
# source("./auto_outlying_MST.R")

outputDirectory <- gsub("NEW_DELETE_POING/new_delete_point", "NEW_MEASURE/Skinny", backupDirectory)
# print(outputDirectory)
# source("./auto_alpha.R")

outputDirectory <- gsub("NEW_DELETE_POING/new_delete_point", "NEW_MEASURE/Stringy", backupDirectory)
# print(outputDirectory)
# source("./auto_diameter_point.R")

outputDirectory <- gsub("NEW_DELETE_POING/new_delete_point", "NEW_MEASURE/Straited", backupDirectory)
# print(outputDirectory)
# source("./auto_straited.R")
