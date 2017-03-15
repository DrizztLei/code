library(ggplot2)
library(methods)
library(rJava)
library(scagnostics)

args <- commandArgs()

directory <- args[6]
originName <- args[7]
outputDirectory <- args[8]

fileDirectory <- read.csv(directory, head = FALSE)
fileDirectory <- fileDirectory[[1]]

fileOriginName <- read.csv(originName, head = FALSE)
fileOriginName <- fileOriginName[[1]]

fileOutputDirectory <- read.csv(outputDirectory, head = FALSE)
fileOutputDirectory <- fileOutputDirectory[[1]]

for(item in seq(1, length(fileOutputDirectory)))
{
    backupDirectory <- fileOutputDirectory[item]

    directory <- fileDirectory[item]
    originName <- fileOriginName[item]
    outputDirectory <- fileOutputDirectory[item]

    source_file = paste(directory, originName, ".csv", sep = "")

    print(source_file)

    info <- read.csv(source_file, head = FALSE)

    x <- info[[1]]
    y <- info[[2]]

    rx <- max(x) - min(x)
    ry <- max(y) - min(y)

    y <- y * rx / ry

    result <- scagnostics(data.frame(x, y))

    outputDirectory <- gsub("NEW_DELETE_POINT/new_delete_point", "NEW_MEASURE/Clumpy", backupDirectory)
    # print(outputDirectory)
    source("./auto_clumpy.R")

    outputDirectory <- gsub("NEW_DELETE_POINT/new_delete_point", "NEW_MEASURE/Convex", backupDirectory)
    # print(outputDirectory)
    source("./auto_convex.R")

    outputDirectory <- gsub("NEW_DELETE_POINT/new_delete_point", "NEW_MEASURE/Skewed", backupDirectory)
    # print(outputDirectory)
    source("./auto_skewed.R")

    outputDirectory <- gsub("NEW_DELETE_POINT/new_delete_point", "NEW_MEASURE/Outlying_MST", backupDirectory)
    # print(outputDirectory)
    source("./auto_outlying_MST.R")

    outputDirectory <- gsub("NEW_DELETE_POINT/new_delete_point", "NEW_MEASURE/Skinny", backupDirectory)
    # print(outputDirectory)
    source("./auto_alpha.R")

    outputDirectory <- gsub("NEW_DELETE_POINT/new_delete_point", "NEW_MEASURE/Stringy", backupDirectory)
    # print(outputDirectory)
    source("./auto_diameter_point.R")

    outputDirectory <- gsub("NEW_DELETE_POINT/new_delete_point", "NEW_MEASURE/Straited", backupDirectory)
    # print(outputDirectory)
    source("./auto_straited.R")
}