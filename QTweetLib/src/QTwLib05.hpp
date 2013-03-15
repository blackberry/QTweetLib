// Default empty project template
#ifndef QTwLib05_HPP_
#define QTwLib05_HPP_

#include <QObject>

namespace bb { namespace cascades { class Application; }}

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class QTwLib05 : public QObject
{
    Q_OBJECT
public:
    QTwLib05(bb::cascades::Application *app);
    virtual ~QTwLib05() {}
};


#endif /* QTwLib05_HPP_ */
