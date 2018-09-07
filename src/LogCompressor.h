#ifndef LOGCOMPRESSOR_H
#define LOGCOMPRESSOR_H

#include <QThread>

class LogCompressor : public QThread
{
    Q_OBJECT
public:
    /** @brief Create the log compressor. It will only get active upon calling startCompression() */
    /** @brief 로그 압축기를 만듭니다. startCompression () 호출시에만 활성화됩니다 */
    LogCompressor(QString logFileName, QString outFileName="", QString delimiter="\t");
    /** @brief Start the compression of a raw, line-based logfile into a CSV file */
    /** @brief 원시 행 기반 로그 파일을 CSV 파일로 압축 시작 */
    void startCompression(bool holeFilling=false);
    bool isFinished();
    int getCurrentLine();

protected:
    void run();                     ///< This function actually performs the compression. It's an overloaded function from QThread
                                    /// <이 함수는 실제로 압축을 수행합니다. QThread에서 오버로드 된 함수입니다.
    QString logFileName;            ///< The input file name.
                                    /// <입력 파일 이름.
    QString outFileName;            ///< The output file name. If blank defaults to logFileName
                                    /// <출력 파일 이름. 공백으로 기본값이 logFileName 인 경우
    bool running;                   ///< True when the startCompression() function is operating.
                                    /// <startCompression () 함수가 작동 중일 때 true입니다.
    int currentDataLine;            ///< The current line of data that is being processed. Only relevant when running==true
                                    /// <처리중인 현재 데이터 행. 실행 중일 때만 관련 == true
    QString delimiter;              ///< Delimiter between fields in the output file. Defaults to tab ('\t')
                                    /// <출력 파일의 필드 사이를 구분합니다. 기본값은 탭 ( '\ t')입니다.
    bool holeFillingEnabled;        ///< Enables the filling of holes in the dataset with the previous value (or NaN if none exists)
                                    /// <데이터 세트의 구멍을 이전 값으로 채 웁니다 (존재하지 않으면 NaN).
signals:
    /** @brief This signal is emitted when there is a change in the status of the parsing algorithm. For instance if an error is encountered.
     * @param status A status message
     */
    /** brief이 신호는 파싱 알고리즘의 상태가 변경 될 때 출력됩니다. 예를 들어 오류가 발생한 경우.
     * @param status 상태 메세지
     */
    void logProcessingStatusChanged(QString status);

    /** @brief This signal is emitted once a logfile has been finished writing
     * @param fileName The name of the output (CSV) file
     */
    /** @ brief이 신호는 로그 파일의 쓰기가 끝나면 출력됩니다.
     * @param fileName 출력 (CSV) 파일의 이름
     */
    void finishedFile(QString fileName);
};

#endif // LOGCOMPRESSOR_H
