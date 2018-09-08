#include "JlCompress.h"
#include <QDebug>

static bool copyData(QIODevice &inFile, QIODevice &outFile)
{
    while (!inFile.atEnd()) {
        char buf[4096];
        qint64 readLen = inFile.read(buf, 4096);
        if (readLen <= 0)
            return false;
        if (outFile.write(buf, readLen) != readLen)
            return false;
    }
    return true;
}

/**OK
 * Comprime il file fileName, nell'oggetto zip, con il nome fileDest.
 *
 * La funzione fallisce se:
 * * zip==NULL;
 * * l'oggetto zip e stato aperto in una modalita non compatibile con l'aggiunta di file;
 * * non e possibile aprire il file d'origine;
 * * non e possibile creare il file all'interno dell'oggetto zip;
 * * si e rilevato un errore nella copia dei dati;
 * * non e stato possibile chiudere il file all'interno dell'oggetto zip;
 */

/*
 * Compile il file fileName, nell'oggetto zip, fileDest와 일치합니다.
 *
 * La funzione fallisce se :
 * * zip == NULL;
 * * 호환되지 않는 파일 형식으로 파일을 압축하고 파일을 압축합니다.
 * * 가능하지 않은 응용 프로그램 파일 원본;
 * * 불가능할 가능성이있는 파일 all'interno dell'oggetto zip;
 * * 오류 메시지가 발생했습니다.
 * * 비 전자 화일 가능성이있는 파일 all'interno dell'oggetto zip;
*/

bool JlCompress::compressFile(QuaZip* zip, QString fileName, QString fileDest) {
    // zip: oggetto dove aggiungere il file
    // fileName: nome del file reale
    // fileDest: nome del file all'interno del file compresso

/*
    // zip : oggetto dove aggiungere il file
    // fileName : 파일 이름 reale
    // fileDest : nome del file all'interno del file compresso
*/


    // Controllo l'apertura dello zip
    if (!zip) return false;
    if (zip->getMode()!=QuaZip::mdCreate &&
        zip->getMode()!=QuaZip::mdAppend &&
        zip->getMode()!=QuaZip::mdAdd) return false;

    // Apro il file originale	Apro il 파일 원본
    QFile inFile;
    inFile.setFileName(fileName);
    if(!inFile.open(QIODevice::ReadOnly)) return false;

    // Apro il file risulato
    QuaZipFile outFile(zip);
    if(!outFile.open(QIODevice::WriteOnly, QuaZipNewInfo(fileDest, inFile.fileName()))) return false;

    // Copio i dati
    if (!copyData(inFile, outFile) || outFile.getZipError()!=UNZ_OK) {
        return false;
    }

    // Chiudo i file
    outFile.close();
    if (outFile.getZipError()!=UNZ_OK) return false;
    inFile.close();

    return true;
}

/**OK
 * Comprime la cartella dir nel file fileCompressed, se recursive e true allora
 * comprime anche le sotto cartelle. I nomi dei file preceduti dal path creato
 * togliendo il pat della cartella origDir al path della cartella dir.
 * Se la funzione fallisce restituisce false e cancella il file che si e tentato
 * di creare.
 *
 * La funzione fallisce se:
 * * zip==NULL;
 * * l'oggetto zip e stato aperto in una modalita non compatibile con l'aggiunta di file;
 * * la cartella dir non esiste;
 * * la compressione di una sotto cartella fallisce (1);
 * * la compressione di un file fallisce;
 * (1) La funzione si richiama in maniera ricorsiva per comprimere le sotto cartelle
 * dunque gli errori di compressione di una sotto cartella sono gli stessi di questa
 * funzione.
 */

/*
 * Comprime la cartella 디렉토리 파일 fileCompressed, se 재귀 적 e true allora
* anche le sotto cartelle을 (를) 포함합니다. 나는 파일 경로 선행 경로를 알 수있다.
 * todliendo il pat della cartella origDir al 경로 della cartella dir.
 * 파일 저장시 파일 저장 실패
 * 디 creare.
 *
 * La funzione fallisce se :
 * * zip == NULL;
 * * 호환되지 않는 파일 형식으로 파일을 압축하고 파일을 압축합니다.
 * * la cartella dir non esiste;
 * * 압축률은 카멜라와 유사 함 (1);
 * * 압축 파일의 낙오;
 * (1) 컴플리트 상품에 따라 리치감이있는 리치몬드
 *이 사진은 다음 콘테스트에 제출되었습니다
 * funzione.
*/

bool JlCompress::compressSubDir(QuaZip* zip, QString dir, QString origDir, bool recursive) {
    // zip: oggetto dove aggiungere il file
    // dir: cartella reale corrente
    // origDir: cartella reale originale
    // (path(dir)-path(origDir)) = path interno all'oggetto zip

/*
    // zip : oggetto dove aggiungere il file
    // dir : 카르텔 리알 코 렌테
    // origDir : Cartel reale originale
    // (path (dir) -path (origDir)) = 경로 내부 all'oggetto zip
*/


    // Controllo l'apertura dello zip
    if (!zip) return false;
    if (zip->getMode()!=QuaZip::mdCreate &&
        zip->getMode()!=QuaZip::mdAppend &&
        zip->getMode()!=QuaZip::mdAdd) return false;

    // Controllo la cartella
    QDir directory(dir);
    if (!directory.exists()) return false;

    // Se comprimo anche le sotto cartelle
    if (recursive) {
        // Per ogni sotto cartella
        QFileInfoList files = directory.entryInfoList(QDir::AllDirs|QDir::NoDotAndDotDot);
        Q_FOREACH (QFileInfo file, files) {
            // Comprimo la sotto cartella
            if(!compressSubDir(zip,file.absoluteFilePath(),origDir,recursive)) return false;
        }
    }

    // Per ogni file nella cartella
    QFileInfoList files = directory.entryInfoList(QDir::Files);
    QDir origDirectory(origDir);
    Q_FOREACH (QFileInfo file, files) {
        // Se non e un file o e il file compresso che sto creando
        if(!file.isFile()||file.absoluteFilePath()==zip->getZipName()) continue;

        // Creo il nome relativo da usare all'interno del file compresso
        QString filename = origDirectory.relativeFilePath(file.absoluteFilePath());

        // Comprimo il file
        if (!compressFile(zip,file.absoluteFilePath(),filename)) return false;
    }

    return true;
}

/**OK
 * Estrae il file fileName, contenuto nell'oggetto zip, con il nome fileDest.
 * Se la funzione fallisce restituisce false e cancella il file che si e tentato di estrarre.
 *
 * La funzione fallisce se:
 * * zip==NULL;
 * * l'oggetto zip e stato aperto in una modalita non compatibile con l'estrazione di file;
 * * non e possibile aprire il file all'interno dell'oggetto zip;
 * * non e possibile creare il file estratto;
 * * si e rilevato un errore nella copia dei dati (1);
 * * non e stato possibile chiudere il file all'interno dell'oggetto zip (1);
 *
 * (1): prima di uscire dalla funzione cancella il file estratto.
 */

/*
 * 파일 이름, 파일 이름, 파일 이름과 일치하지 않는 파일 이름.
 * 파일 삭제시 파일 삭제를 취소 할 수 있습니다.
 *
 * La funzione fallisce se :
 * * zip == NULL;
 * * 파일과 파일을 호환 할 수 없으며 파일을 압축 할 수 없습니다.
 * * 불가능할 수있는 모든 파일 all'interno dell'oggetto zip;
 * * 불가능할 수있는 creare il 파일 estratto;
 * * 오류 메시지가 나타나지 않습니다 (1);
 * * 모든 사람이 사용할 수있는 파일이 아닌 모든 파일 (1);
 *
 * (1) : 파일을 다운로드 할 수 있습니다.
*/

bool JlCompress::extractFile(QuaZip* zip, QString fileName, QString fileDest) {
    // zip: oggetto dove aggiungere il file
    // filename: nome del file reale
    // fileincompress: nome del file all'interno del file compresso

    // Controllo l'apertura dello zip
    if (!zip) return false;
    if (zip->getMode()!=QuaZip::mdUnzip) return false;

    // Apro il file compresso
    if (!fileName.isEmpty())
        zip->setCurrentFile(fileName);
    QuaZipFile inFile(zip);
    if(!inFile.open(QIODevice::ReadOnly) || inFile.getZipError()!=UNZ_OK) return false;

    // Controllo esistenza cartella file risultato
    QDir curDir;
    if (!curDir.mkpath(QFileInfo(fileDest).absolutePath())) {
        return false;
    }

    QuaZipFileInfo info;
    if (!zip->getCurrentFileInfo(&info))
        return false;

    if (fileDest.endsWith('/') && QFileInfo(fileDest).isDir()) {
        return QFile(fileDest).setPermissions(info.getPermissions());
    }

    // Apro il file risultato
    QFile outFile;
    outFile.setFileName(fileDest);
    if(!outFile.open(QIODevice::WriteOnly)) return false;

    // Copio i dati
    if (!copyData(inFile, outFile) || inFile.getZipError()!=UNZ_OK) {
        outFile.close();
        removeFile(QStringList(fileDest));
        return false;
    }
    outFile.close();

    // Chiudo i file
    inFile.close();
    if (inFile.getZipError()!=UNZ_OK) {
        removeFile(QStringList(fileDest));
        return false;
    }

    return outFile.setPermissions(info.getPermissions());
}

/**
 * Rimuove i file il cui nome e specificato all'interno di listFile.
 * Restituisce true se tutti i file sono stati cancellati correttamente, attenzione
 * perche puo restituire false anche se alcuni file non esistevano e si e tentato
 * di cancellarli.
 */

/*
 * 파일 이름과 파일명을 모두 지우십시오.
 * 사실을 기록하고 파일을 삭제하는 법, attenzione
 * perche puo restituire는 false로 설정되어 있습니다.
 * 디 카 탈리.
*/

bool JlCompress::removeFile(QStringList listFile) {
    bool ret = true;
    // Per ogni file
    for (int i=0; i<listFile.count(); i++) {
        // Lo elimino
        ret = ret && QFile::remove(listFile.at(i));
    }
    return ret;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/**OK
 * Comprime il file fileName nel file fileCompressed.
 * Se la funzione fallisce restituisce false e cancella il file che si e tentato
 * di creare.
 *
 * La funzione fallisce se:
 * * non si riesce ad aprire l'oggetto zip;
 * * la compressione del file fallisce;
 * * non si riesce a chiudere l'oggetto zip;
 */

/*
 * Compile il file fileName 파일 file 압축 된 파일.
 * 파일 저장시 파일 저장 실패
 * 디 creare.
 *
 * La funzione fallisce se :
 * * 비 계약 광고는 이전과 동일합니다.
 * * 압축 파일의 오류;
 * * 비생산적이지는 않습니다.
*/

bool JlCompress::compressFile(QString fileCompressed, QString file) {
    // Creo lo zip
    QuaZip zip(fileCompressed);
    QDir().mkpath(QFileInfo(fileCompressed).absolutePath());
    if(!zip.open(QuaZip::mdCreate)) {
        QFile::remove(fileCompressed);
        return false;
    }

    // Aggiungo il file
    if (!compressFile(&zip,file,QFileInfo(file).fileName())) {
        QFile::remove(fileCompressed);
        return false;
    }

    // Chiudo il file zip
    zip.close();
    if(zip.getZipError()!=0) {
        QFile::remove(fileCompressed);
        return false;
    }

    return true;
}

/**OK
 * Comprime i file specificati in files nel file fileCompressed.
 * Se la funzione fallisce restituisce false e cancella il file che si e tentato
 * di creare.
 *
 * La funzione fallisce se:
 * * non si riesce ad aprire l'oggetto zip;
 * * la compressione di un file fallisce;
 * * non si riesce a chiudere l'oggetto zip;
 */

/*
 * Comprime 나는 파일 fileCompressed의 특정 파일을 압축합니다.
 * 파일 저장시 파일 저장 실패
 * 디 creare.
 *
 * La funzione fallisce se :
 * * 비 계약 광고는 이전과 동일합니다.
 * * 압축 파일의 낙오;
 * * 비생산적이지는 않습니다.
*/

bool JlCompress::compressFiles(QString fileCompressed, QStringList files) {
    // Creo lo zip
    QuaZip zip(fileCompressed);
    QDir().mkpath(QFileInfo(fileCompressed).absolutePath());
    if(!zip.open(QuaZip::mdCreate)) {
        QFile::remove(fileCompressed);
        return false;
    }

    // Comprimo i file
    QFileInfo info;
    Q_FOREACH (QString file, files) {
        info.setFile(file);
        if (!info.exists() || !compressFile(&zip,file,info.fileName())) {
            QFile::remove(fileCompressed);
            return false;
        }
    }

    // Chiudo il file zip
    zip.close();
    if(zip.getZipError()!=0) {
        QFile::remove(fileCompressed);
        return false;
    }

    return true;
}

/**OK
 * Comprime la cartella dir nel file fileCompressed, se recursive e true allora
 * comprime anche le sotto cartelle.
 * Se la funzione fallisce restituisce false e cancella il file che si e tentato
 * di creare.
 *
 * La funzione fallisce se:
 * * non si riesce ad aprire l'oggetto zip;
 * * la compressione di un file fallisce;
 * * non si riesce a chiudere l'oggetto zip;
 */

/*
 * Comprime la cartella 디렉토리 파일 fileCompressed, se 재귀 적 e true allora
 * anche le sotto cartelle을 (를) 포함합니다.
 * 파일 저장시 파일 저장 실패
 * 디 creare.
 *
 * La funzione fallisce se :
 * * 비 계약 광고는 이전과 동일합니다.
 * * 압축 파일의 낙오;
 * * 비생산적이지는 않습니다.
*/

bool JlCompress::compressDir(QString fileCompressed, QString dir, bool recursive) {
    // Creo lo zip
    QuaZip zip(fileCompressed);
    QDir().mkpath(QFileInfo(fileCompressed).absolutePath());
    if(!zip.open(QuaZip::mdCreate)) {
        QFile::remove(fileCompressed);
        return false;
    }

    // Aggiungo i file e le sotto cartelle
    if (!compressSubDir(&zip,dir,dir,recursive)) {
        QFile::remove(fileCompressed);
        return false;
    }

    // Chiudo il file zip
    zip.close();
    if(zip.getZipError()!=0) {
        QFile::remove(fileCompressed);
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/**OK
 * Estrae il file fileName, contenuto nel file fileCompressed, con il nome fileDest.
 * Se fileDest = "" allora il file viene estratto con lo stesso nome con cui e
 * stato compresso.
 * Se la funzione fallisce cancella il file che si e tentato di estrarre.
 * Restituisce il nome assoluto del file estratto.
 *
 * La funzione fallisce se:
 * * non si riesce ad aprire l'oggetto zip;
 * * l'estrazione del file fallisce;
 * * non si riesce a chiudere l'oggetto zip;
 */

/*
 * 파일 fileName은 파일 fileCompressed, 파일 file과 동등합니다.
 * Se fileDest = "" "" "" "" "" ""
 * stato 압축.
 * 취소 할 때 취소 수수료가 부과됩니다.
 * estratto 파일을 따로 저장하십시오.
 *
 * La funzione fallisce se :
 * * 비 계약 광고는 이전과 동일합니다.
 * * l' estrazione del file fallisce;
 * * 비생산적이지는 않습니다.
*/

QString JlCompress::extractFile(QString fileCompressed, QString fileName, QString fileDest) {
    // Apro lo zip
    QuaZip zip(fileCompressed);
    if(!zip.open(QuaZip::mdUnzip)) {
        return QString();
    }

    // Estraggo il file
    if (fileDest.isEmpty()) 
        fileDest = fileName;
    if (!extractFile(&zip,fileName,fileDest)) {
        return QString();
    }

    // Chiudo il file zip
    zip.close();
    if(zip.getZipError()!=0) {
        removeFile(QStringList(fileDest));
        return QString();
    }
    return QFileInfo(fileDest).absoluteFilePath();
}

/**OK
 * Estrae i file specificati in files, contenuti nel file fileCompressed, nella
 * cartella dir. La struttura a cartelle del file compresso viene rispettata.
 * Se dir = "" allora il file viene estratto nella cartella corrente.
 * Se la funzione fallisce cancella i file che si e tentato di estrarre.
 * Restituisce i nomi assoluti dei file estratti.
 *
 * La funzione fallisce se:
 * * non si riesce ad aprire l'oggetto zip;
 * * l'estrazione di un file fallisce;
 * * non si riesce a chiudere l'oggetto zip;
 */

/*
 * 특정 파일을 파일에 저장하고, 파일 fileCompressed, nella
* 카텔라 디렉터. 라 Struttura 및 카르텔 파일 압축을 풉니 다.
 * Se dir = ""모든 파일은 비공개 파일입니다.
 * 취소시 파일을 삭제할 수 있습니다.
 * Restituisce는 내가 estratti 파일을 가지고 있다고 생각합니다.
 *
 * La funzione fallisce se :
 * * 비 계약 광고는 이전과 동일합니다.
 * * 나는 파일을 잃어 버렸다.
 * * 비생산적이지는 않습니다.
*/

QStringList JlCompress::extractFiles(QString fileCompressed, QStringList files, QString dir) {
    // Creo lo zip
    QuaZip zip(fileCompressed);
    if(!zip.open(QuaZip::mdUnzip)) {
        return QStringList();
    }

    // Estraggo i file
    QStringList extracted;
    for (int i=0; i<files.count(); i++) {
        QString absPath = QDir(dir).absoluteFilePath(files.at(i));
        if (!extractFile(&zip, files.at(i), absPath)) {
            removeFile(extracted);
            return QStringList();
        }
        extracted.append(absPath);
    }

    // Chiudo il file zip
    zip.close();
    if(zip.getZipError()!=0) {
        removeFile(extracted);
        return QStringList();
    }

    return extracted;
}

/**OK
 * Estrae il file fileCompressed nella cartella dir.
 * Se dir = "" allora il file viene estratto nella cartella corrente.
 * Se la funzione fallisce cancella i file che si e tentato di estrarre.
 * Restituisce i nomi assoluti dei file estratti.
 *
 * La funzione fallisce se:
 * * non si riesce ad aprire l'oggetto zip;
 * * la compressione di un file fallisce;
 * * non si riesce a chiudere l'oggetto zip;
 */

/*
 * Estrae il file file 압축 된 첼로 파일입니다.
 * Se dir = ""모든 파일은 비공개 파일입니다.
 * 취소시 파일을 삭제할 수 있습니다.
 * Restituisce는 내가 estratti 파일을 가지고 있다고 생각합니다.
 *
 * La funzione fallisce se :
 * * 비 계약 광고는 이전과 동일합니다.
 * * 압축 파일의 낙오;
 * * 비생산적이지는 않습니다.
*/

QStringList JlCompress::extractDir(QString fileCompressed, QString dir) {
    // Apro lo zip
    QuaZip zip(fileCompressed);
    if(!zip.open(QuaZip::mdUnzip)) {
        return QStringList();
    }

    QDir directory(dir);
    QStringList extracted;
    if (!zip.goToFirstFile()) {
        return QStringList();
    }
    do {
        QString name = zip.getCurrentFileName();
        QString absFilePath = directory.absoluteFilePath(name);
        if (!extractFile(&zip, "", absFilePath)) {
            removeFile(extracted);
            return QStringList();
        }
        extracted.append(absFilePath);
    } while (zip.goToNextFile());

    // Chiudo il file zip
    zip.close();
    if(zip.getZipError()!=0) {
        removeFile(extracted);
        return QStringList();
    }

    return extracted;
}

/**OK
 * Restituisce la lista dei file resenti nel file compresso fileCompressed.
 * Se la funzione fallisce, restituisce un elenco vuoto.
 *
 * La funzione fallisce se:
 * * non si riesce ad aprire l'oggetto zip;
 * * la richiesta di informazioni di un file fallisce;
 * * non si riesce a chiudere l'oggetto zip;
 */

/*
 * 파일 압축 파일 압축 해제 파일을 복원합니다.
 * 휴식을 취하기, 휴식을 취하기.
 *
 * La funzione fallisce se :
 * * 비 계약 광고는 이전과 동일합니다.
 * * 파일 올리기에 대한 정보를 제공합니다.
 * * 비생산적이지는 않습니다.
*/

QStringList JlCompress::getFileList(QString fileCompressed) {
    // Apro lo zip
    QuaZip* zip = new QuaZip(QFileInfo(fileCompressed).absoluteFilePath());
    if(!zip->open(QuaZip::mdUnzip)) {
        delete zip;
        return QStringList();
    }

    // Estraggo i nomi dei file
    QStringList lst;
    QuaZipFileInfo info;
    for(bool more=zip->goToFirstFile(); more; more=zip->goToNextFile()) {
      if(!zip->getCurrentFileInfo(&info)) {
          delete zip;
          return QStringList();
      }
      lst << info.name;
      //info.name.toLocal8Bit().constData()
    }

    // Chiudo il file zip
    zip->close();
    if(zip->getZipError()!=0) {
        delete zip;
        return QStringList();
    }
    delete zip;

    return lst;
}

