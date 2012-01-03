/**
 * Hamlog
 *
 * Copyright (C) 2011, Jan Kaluza <hanzz.k@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#pragma once

#include <QtCore>
#include <QApplication>
#include "ui_connectdialog.h"
#include "connection.h"

class ConnectDialog : public QDialog {
	Q_OBJECT

	public:
		ConnectDialog(QWidget *parent);

	signals:
		void onConnectServer(const QString &server, int port, const QString &username, const QString &password);
		void onRegisterAccount(const QString &server, int port, const QString &username, const QString &password);

	private slots:
		void connectServer();
		void registerAccount();

	private:
		Ui_ConnectDialog ui;
};