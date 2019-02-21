//
// Created by Hannes on 14/02/2019.
//

#ifndef MSCORE_QPROGRESS_H
#define MSCORE_QPROGRESS_H


class QProgress : public Progress {
public:
    QProgress(QLabel* messageLabel);
private:
    QLabel* messageLabel;
};


#endif //MSCORE_QPROGRESS_H
