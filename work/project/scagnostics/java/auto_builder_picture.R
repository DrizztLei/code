library(ggplot2)
library(methods)
library(rJava)
library(scagnostics)

args <- commandArgs()

# print(args[6])
# print(args[8])
# print(args[7])

directory <- args[6]
originName <- args[7]
outputDirectory <- args[8]

backupDirectory <- outputDirectory

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
source("./auto_skewed.R")

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
