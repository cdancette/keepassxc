/*
*  Copyright (C) 2018 KeePassXC Team <team@keepassxc.org>
*  Copyright (C) 2010 Felix Geyer <debfx@fobos.de>
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 2 or (at your option)
*  version 3 of the License.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KEEPASSX_COMPOSITEKEY_H
#define KEEPASSX_COMPOSITEKEY_H

#include <QList>
#include <QSharedPointer>
#include <QString>

#include "crypto/kdf/Kdf.h"
#include "keys/ChallengeResponseKey.h"
#include "keys/Key.h"

class CompositeKey : public Key
{
public:
    CompositeKey();
    Q_DISABLE_COPY(CompositeKey);
    ~CompositeKey() override;
    void clear();
    bool isEmpty() const;

    QByteArray rawKey() const override;
    QByteArray rawKey(const QByteArray* transformSeed, bool* ok = nullptr) const;
    bool transform(const Kdf& kdf, QByteArray& result) const Q_REQUIRED_RESULT;
    bool challenge(const QByteArray& seed, QByteArray& result) const;

    void addKey(QSharedPointer<Key> key);

    void addChallengeResponseKey(QSharedPointer<ChallengeResponseKey> key);

private:
    QList<QSharedPointer<Key>> m_keys;
    QList<QSharedPointer<ChallengeResponseKey>> m_challengeResponseKeys;
};

#endif // KEEPASSX_COMPOSITEKEY_H
