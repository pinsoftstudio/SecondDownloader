#include "header/propertydialog.h"
#include "ui_propertydialog.h"
#include "QFile"
#include "QDir"
#include "QFileInfo"
#include "QFileIconProvider"
#include "QDesktopServices"
#include "QMessageBox"
#include "QClipboard"
#include "dialogcrtinf.h"
PropertyDialog::PropertyDialog(QString url, QString location, QString state,QString size, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PropertyDialog)
{
    ui->setupUi(this);
    Url=url;
    Location=location;
    State=state;
    Size=size;
    if(QFile(QDir::fromNativeSeparators(Location)).exists()){
        ui->lineLocation->setText(Location);
        ui->btnOpen->setEnabled(1);
    }else{
        ui->lineLocation->setText(tr("文件不存在"));
        if(QDir(QFileInfo(QDir::fromNativeSeparators(Location)).absolutePath()).exists()){
            ui->btnOpen->setEnabled(0);
        }

    }
    ui->labName->setText(QFileInfo(QDir::fromNativeSeparators(Location)).fileName());
    QString type=QFileInfo(QDir::fromNativeSeparators(Location)).suffix();
    ui->labtype->setText(ProgetFileTypeByExtension(type));
    ui->lineurl->setText(Url);
    ui->labstate->setText(State);
    ui->labsize->setText(Size);
    QPixmap pix=QFileIconProvider().icon(QFileInfo(QDir::fromNativeSeparators(Location))).pixmap(60,60);
    ui->labico->setPixmap(pix);
    ui->lineLocation->setReadOnly(1);
    ui->lineurl->setReadOnly(1);
    ui->btnOk->setProperty("highlight","true");
    setAttribute(Qt::WA_DeleteOnClose);


}

PropertyDialog::~PropertyDialog()
{
    delete ui;
}

void PropertyDialog::on_btnOpen_clicked()
{
    if(!QDesktopServices::openUrl(QFileInfo(QDir::fromNativeSeparators(Location)).absolutePath())){
        QMessageBox::critical(this,tr("错误"),tr("打开文件夹失败！"),tr("确定"));
    }

}


void PropertyDialog::on_btnCopy_clicked()
{
    QClipboard *clip=QApplication::clipboard();
    clip->setText(Url);
    DialogCrtInf dialog;
    QString title=tr("提示");
    QString content=tr("已复制到剪贴板！");
    dialog.setText(content);
    dialog.setTitle(title);
    dialog.exec();

}

QString  PropertyDialog::ProgetFileTypeByExtension(const QString &extension) {
    // 使用QMap来存储文件扩展名与文件类型的映射
    // 注意：这里使用小写字母来避免大小写敏感问题

        QMap<QString, QString> fileTypeMap= {
            {"txt", "文本文件"},
            {"doc", "Word文档"},
            {"docx", "Word文档（新版）"},
            {"xls", "Excel电子表格（旧版）"},
            {"xlsx", "Excel电子表格（新版）"},
            {"ppt", "PowerPoint演示文稿（旧版）"},
            {"pptx", "PowerPoint演示文稿（新版）"},
            {"pdf", "PDF文档"},
            {"jpg", "JPEG图片"},
            {"jpeg", "JPEG图片"},
            {"png", "PNG图片"},
            {"gif", "GIF图片"},
            {"bmp", "BMP图片"},
            {"tif", "TIFF图片"},
            {"tiff", "TIFF图片"},
            {"mp3", "MP3音频文件"},
            {"wav", "WAV音频文件"},
            {"aac", "AAC音频文件"},
            {"flac", "FLAC音频文件（自由无损音频压缩）"},
            {"ogg", "Ogg Vorbis音频文件"},
            {"m4a", "M4A音频文件（常用于Apple设备）"},
            {"mp4", "MP4视频文件（支持视频和音频）"},
            {"avi", "AVI视频文件"},
            {"mov", "MOV视频文件（Apple QuickTime）"},
            {"wmv", "WMV视频文件（Windows Media Video）"},
            {"flv", "FLV视频文件（常用于网页视频）"},
            {"mkv", "MKV视频文件（Matroska格式）"},
            {"webm", "WebM视频文件（基于VP8/VP9和Vorbis/Opus）"},
            {"3gp", "3GP视频文件（用于移动设备）"},
            {"ts", "TS视频文件（MPEG传输流）"},
            {"m3u8", "M3U8播放列表文件（用于HLS流媒体）"},
            {"srt", "SRT字幕文件"},
            {"ass", "ASS字幕文件（高级字幕系统）"},
            {"ssa", "SSA字幕文件（与ASS相似）"},
            {"lrc", "LRC歌词文件"},
            {"chm", "CHM帮助文件（Microsoft Compiled HTML Help）"},
            {"hlp", "HLP帮助文件（旧的Windows帮助格式）"},
            {"sql", "SQL数据库查询文件"},
            {"db", "数据库文件（通用）"},
            {"sqlite", "SQLite数据库文件（.sqlite3或.db）"},
            {"mdb", "Microsoft Access数据库文件（MDB）"},
            {"accdb", "Microsoft Access数据库文件（ACCDB，新格式）"},
            {"zip", "ZIP压缩文件"},
            {"rar", "RAR压缩文件"},
            {"tar", "TAR压缩文件"},
            {"gz", "GZIP压缩文件"},
            {"bz2", "BZIP2压缩文件"},
            {"7z", "7-Zip压缩文件"},
            {"iso", "ISO光盘映像文件"},
            {"dmg", "DMG磁盘映像文件（Mac OS X）"},
            {"html", "HTML网页文件"},
            {"htm", "HTML网页文件（旧版）"},
            {"php", "PHP网页脚本文件"},
            {"asp", "ASP网页脚本文件（Active Server Pages）"},
            {"aspx", "ASP.NET网页脚本文件"},
            {"jsp", "JSP网页脚本文件（Java Server Pages）"},
            {"css", "CSS样式表文件"},
            {"scss", "SCSS样式表文件（Sassy CSS）"},
            {"sass", "Sass样式表文件（Syntactically Awesome Stylesheets）"},
            {"less", "LESS样式表文件（Leaner CSS）"},
            {"js", "JavaScript脚本文件"},
            {"jsx", "JSX文件（JavaScript XML，React的JS扩展）"},
            {"ts", "TypeScript文件（JavaScript的超集）"},{"json", "JSON数据交换文件"},
        {"xml", "XML数据标记文件"},
        {"yaml", "YAML数据序列化文件"},
        {"csv", "CSV逗号分隔值文件"},
        {"tsv", "TSV制表符分隔值文件"},
        {"xlsxm", "Excel宏启用工作簿（.xlsm）"},
        {"xlsb", "Excel二进制工作簿（.xlsb）"},
        {"xltx", "Excel模板（.xltx）"},
        {"xltm", "Excel宏启用模板（.xltm）"},
        {"potx", "PowerPoint模板（.potx）"},
        {"potm", "PowerPoint宏启用模板（.potm）"},
        {"ppsx", "PowerPoint放映（.ppsx）"},
        {"ppsm", "PowerPoint宏启用放映（.ppsm）"},
        {"rtf", "RTF富文本格式文件"},
        {"odt", "ODT开放文档文本文件（OpenDocument Text）"},
        {"ods", "ODS开放文档电子表格文件（OpenDocument Spreadsheet）"},
        {"odp", "ODP开放文档演示文稿文件（OpenDocument Presentation）"},
        {"epub", "EPUB电子书文件"},
        {"mobi", "MOBI电子书文件（Kindle）"},
        {"azw", "AZW电子书文件（Kindle旧版）"},
        {"azw3", "AZW3电子书文件（Kindle新版）"},
        {"pdb", "PDB电子书文件（PalmDoc）"},
        {"fb2", "FB2电子书文件（FictionBook 2）"},
        {"djvu", "DJVU电子书和图像文件"},
        {"cbz", "CBZ漫画书归档文件（ZIP）"},
        {"cbr", "CBR漫画书归档文件（RAR）"},
        {"cbt", "CBT漫画书归档文件（TAR）"},
        {"cb7", "CB7漫画书归档文件（7Z）"},
        {"cba", "CBA漫画书归档文件（ACE）"},
        {"lha", "LHA压缩文件（LZH）"},
        {"lzma", "LZMA压缩文件"},
        {"xz", "XZ压缩文件"},
        {"bz", "BZ压缩文件（BZIP压缩的旧格式）"},
        {"tar.gz", "TAR.GZ压缩文件（TAR与GZIP的结合）"},
        {"tar.bz2", "TAR.BZ2压缩文件（TAR与BZIP2的结合）"},
        {"iso.gz", "ISO.GZ压缩文件（ISO与GZIP的结合）"},
        {"rpm", "RPM软件包文件（Red Hat Package Manager）"},
        {"deb", "DEB软件包文件（Debian）"},
        {"apk", "APK安装包文件（Android）"},
        {"ipa", "IPA安装包文件（iOS）"},
        {"xap", "XAP安装包文件（Windows Phone）"},
        {"appx", "APPX安装包文件（Windows 10/11）"},
        {"msi", "MSI安装包文件（Microsoft Installer）"},
        {"dll", "DLL动态链接库文件"},
        {"so", "SO共享对象文件（Linux/Unix）"},
        {"dylib", "DYLIB动态链接库文件（Mac OS X）"},
        {"class", "CLASS Java类文件"},
        {"jar", "JAR Java归档文件"},
        {"war", "WAR Web应用程序归档文件"},
        {"ear", "EAR企业应用程序归档文件"},
        {"rar5", "RAR5压缩文件（RAR的新版本）"},
        {"7z.001", "7-Zip分卷压缩文件（第一分卷）"},
        {"part01.rar", "RAR分卷压缩文件（通用命名）"},
        {"torrent", "Torrent种子文件"},
        {"nfo", "NFO信息文件（通常与软件发布相关）"},
        {"diz", "DIZ描述文件（与DOS软件分发相关）"},
        {"log", "LOG日志文件"},
        {"bak", "BAK备份文件"},
        {"tmp", "TMP临时文件"},
        {"cache", "CACHE缓存文件"},
        {"svg", "SVG可缩放矢量图形文件"},
        {"ai", "AI Adobe Illustrator文件"},
        {"psd", "PSD Adobe Photoshop文档"},
        {"indd", "INDD Adobe InDesign文档"},
        {"dwg", "DWG AutoCAD绘图文件"},
        {"dxf", "DXF AutoCAD绘图交换文件"},
        {"stl", "STL立体光刻文件（3D打印）"},
        {"obj", "OBJ对象文件（3D模型）"},
        {"fbx", "FBX电影盒交换文件"},{"avi", "AVI音频视频交错格式文件"},
        {"mp4", "MP4多媒体容器格式文件"},
        {"mov", "MOV QuickTime影片文件"},
        {"mkv", "MKVMatroska多媒体容器文件"},
        {"flv", "FLVFlash视频文件"},
        {"webm", "WebM网络视频格式文件"},
        {"wmv", "WMVWindows Media视频文件"},
        {"mpeg", "MPEG运动图像专家组视频文件"},
        {"mpg", "MPG同MPEG，旧称"},
        {"ts", "TSMPEG传输流视频文件"},
        {"m4v", "M4VApple的MPEG-4视频文件"},
        {"3gp", "3GPP移动视频格式文件"},
        {"mp3", "MP3MPEG-1 Audio Layer 3音频文件"},
        {"wav", "WAV波形音频文件"},
        {"aac", "AAC高级音频编码文件"},
        {"flac", "FLAC自由无损音频压缩文件"},
        {"ogg", "OggVorbis开源音频压缩文件"},
        {"m4a", "M4AApple的音频文件（包括ALAC）"},
        {"ac3", "AC3杜比数字音频文件"},
        {"dts", "DTS数字影院系统音频文件"},
        {"aiff", "AIFFApple的音频交换文件格式"},
        {"pdf", "PDF可移植文档格式文件"},
        {"tiff", "TIFF标签图像文件格式文件"},
        {"png", "PNG可移植网络图形文件"},
        {"jpg", "JPG/JPEG联合图像专家组文件"},
        {"jpeg", "JPEG同JPG，旧称"},
        {"gif", "GIF图形交换格式文件"},
        {"bmp", "BMP位图图像文件"},
        {"svgz", "SVGZ压缩的SVG文件"},
        {"ico", "ICO图标文件"},
        {"cur", "CUR光标文件"},
        {"ps", "PSPostScript打印文件"},
        {"eps", "EPSEncapsulated PostScript文件"},
        {"latex", "LaTeXLaTeX源代码文件"},
        {"tex", "TeXTeX源代码文件"},
        {"docx", "DOCXMicrosoft Word文档（Open XML）"},
        {"docm", "DOCM宏启用的Word文档（Open XML）"},
        {"dotx", "DOTXWord模板（Open XML）"},
        {"dotm", "DOTM宏启用的Word模板（Open XML）"},
        {"xlsx", "XLSXMicrosoft Excel电子表格（Open XML）"},
        {"xlsm", "XLSM宏启用的Excel电子表格（Open XML）"},
        {"xltx", "XLTXExcel模板（Open XML）"},
        {"xltm", "XLTM宏启用的Excel模板（Open XML）"},
        {"pptx", "PPTXMicrosoft PowerPoint演示文稿（Open XML）"},
        {"pptm", "PPTM宏启用的PowerPoint演示文稿（Open XML）"},
        {"potx", "POTXPowerPoint模板（Open XML）"},
        {"potm", "POTM宏启用的PowerPoint模板（Open XML）"},
        {"ppsx", "PPSXPowerPoint放映（Open XML）"},
        {"ppsm", "PPSM宏启用的PowerPoint放映（Open XML）"},
        {"vsdx", "VSDXVisio绘图文件（Open XML）"},
        {"vsdm", "VSDM宏启用的Visio绘图文件（Open XML）"},
        {"vstm", "VSTMVisio模板（Open XML）"},
        {"vstx", "VSTXVisio模板（Open XML）"},
        {"vssx", "VSSXVisio模具文件（Open XML）"},
        {"vssm", "VSSM宏启用的Visio模具文件（Open XML）"},
        {"vdx", "VDXVisio 2013及以后版本的文件格式"},
        {"vdw", "VDWVisio绘图文件（旧版）"},
        {"vss", "VSSVisio模具文件（旧版）"},
        {"vst", "VSTVisio模板文件（旧版）"},
         {"exe", "可执行文件"},

        };

    // 转换为小写以匹配映射中的键
    QString lowerExtension = extension.toLower();

    // 查找并返回对应的文件类型，如果未找到则返回"未知文件类型"
    if (fileTypeMap.contains(lowerExtension)) {
        return fileTypeMap[lowerExtension];
    } else {
        return extension+"文件";
    }
}
