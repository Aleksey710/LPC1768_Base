import qbs
import qbs.FileInfo
import qbs.ModUtils

Project {
    qbsSearchPaths: "qbs"

    references: [
        "./program/project.qbs",
    ]
}
