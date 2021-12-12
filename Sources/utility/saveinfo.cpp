#include <QDebug>
#include <QDir>
#include <QDataStream>
#include <assert.h>
#include <QDateTime>

#include "Headers/utility/textcode.h"
#include "Headers/utility/saveinfo.h"
#include "Headers/eventlist.h"

SaveInfo::SaveInfo() {

}

SaveInfo::SaveInfo(Character c, RandSummoner rs, EventEnum type, std::string text) {
    attribute = c.getAttributes();
    seed = rs.getSeed();
    stepAMT = rs.getStepAmt();
    eventType = type;
    message = text;
}

SaveInfo SaveInfo::getCurrentSaveInfo(Character c, Event* event, std::string message) {
    return SaveInfo(c, EventList::rs, event->type, message);
}

bool SaveInfo::output(QFile* file) {
    QDataStream out(file);
    if(!out.device()) return false;
    for (int i = 0; i < ATTR_AMT; i++)
        out << attribute.attributes[i];
    out << seed;
    out << stepAMT;
    out << (int)eventType;
    out << codec->fromUnicode(message.c_str());
    return true;
}

bool SaveInfo::input(QFile* file) {
    QDataStream in(file);
    if(!in.device()) return false;
    for (int i = 0; i < ATTR_AMT; i++) {
        in >> attribute.attributes[i];
        if (in.status() != QDataStream::Ok) return false;
    }
    in >> seed;
    if (in.status() != QDataStream::Ok) return false;
    in >> stepAMT;
    if (in.status() != QDataStream::Ok) return false;
    int tmp;
    in >> tmp;
    if (in.status() != QDataStream::Ok) return false;
    eventType = (EventEnum)tmp;

    QByteArray text;
    in >> text;
    if (in.status() != QDataStream::Ok) return false;

    message = codec->toUnicode(text).toStdString();
    return true;
}

FileList::FileList() {
    QDir dir;
    if (!dir.exists(SaveDir)) {
        dir.mkpath(SaveDir);
    }
    assert(dir.exists(SaveDir));
    load_all();
}

FileList::~FileList() {
    free_all();
}

void FileList::load_all() {
    QDir dir(SaveDir);
    list = dir.entryInfoList(QDir::Files, QDir::Name | QDir::Reversed);
    for (int i = 0; i < list.size(); ) {
        if (!check_format(list.at(i))) list.removeAt(i);
        else i++;
    }
    vectorlist.clear();
    for (int i = 0; i < list.size(); i++)
        vectorlist.push_back(list.at(i));
}

void FileList::free_all() {

}

std::string FileList::readable(QFileInfo fileinfo) {
    QString filename = fileinfo.fileName();
    std::string readname = (QDateTime::fromString(filename, "yyyyMMddhhmmss")).toString("yyyy/MM/dd hh:mm:ss").toStdString();
    SaveInfo tmp;
    if (!load_from(tmp, fileinfo)) {
        return "文件损坏";
    }
    readname += " 第" + std::to_string(tmp.attribute[AttributeEnum::term]) + "学期";
    return readname;
}

bool FileList::check_format(QFileInfo fileinfo) {
    SaveInfo tmp;
    if (!load_from(tmp, fileinfo)) return false;
    return true;
}

QString FileList::getCurrentName() {
    return QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
}

bool FileList::save_to_new(SaveInfo info) {
    QString filename = getCurrentName();
    QFile file(SaveDir + QDir::separator() + filename);
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "Create Failed!";
        qDebug() << SaveDir + QDir::separator() + filename;
        return false;
    }
    if (info.output(&file)) {
        file.close();
        load_all();
        return true;
    }
    else return false;
}

bool FileList::save_to(SaveInfo info, QFileInfo fileinfo) {
    QFile file(fileinfo.absoluteFilePath());
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Can't Open Save File";
        return false;
    }
    if (info.output(&file)) {
        file.rename(SaveDir + QDir::separator() + FileList::getCurrentName());
        file.close();
        load_all();
        return true;
    }
    else return false;
}

bool FileList::load_from(SaveInfo& info, QFileInfo fileinfo) {
    QFile file(fileinfo.absoluteFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't Open Save File";
        return false;
    }
    if (info.input(&file)) {
        file.close();
        return true;
    }
    else return false;
}
