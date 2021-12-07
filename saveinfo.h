#ifndef SAVEINFO_H
#define SAVEINFO_H

#include "character.h"
#include "randsummoner.h"
#include <string>
#include <vector>
#include <fstream>
#include <QFile>
#include <QDir>

class SaveInfo {
public:
    SaveInfo();
    SaveInfo(Character, RandSummoner rs, std::string);
    attr attribute;
    int seed, stepAMT;
    std::string message;

    bool output(QFile*);
    bool input(QFile*);

    static SaveInfo getCurrentSaveInfo(Character, std::string);
};

const QString SaveDir = QDir::currentPath() + QDir::separator() + "saves";

class FileList {
public:
    QFileInfoList list;
    std::vector<QFileInfo> vectorlist;

    bool load_from(SaveInfo&, QFileInfo);
    bool save_to_new(SaveInfo);
    bool save_to(SaveInfo, QFileInfo);
    std::string readable(QFileInfo);

    FileList();
    ~FileList();

private:
    static QString getCurrentName();
    void load_all();
    void free_all();
    bool check_format(QFileInfo);
};

#endif // SAVEINFO_H
