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
#include "ui_mainwindow.h"
#include "connection.h"

class QtEventLoop;
class ConnectDialog;

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		MainWindow();
		virtual ~MainWindow();

	public slots:
		void showConnectDialog();
		void showAvailableModules(bool checked = false);
		void showQRZRegisterDialog(bool checked = false);

		void connectServer(const QString &server, int port, const QString &username, const QString &password);
		void registerAccount(const QString &server, int port, const QString &username, const QString &password);

		void handleLoggedIn(HAMConnection *connection);
		void handleLoginFailed(HAMConnection *connection, const QString &reason);
		void handleRegistered(HAMConnection *connection);
		void handleRegistrationFailed(HAMConnection *connection, const QString &reason);

		void handleConnected(HAMConnection *connection);
		void handleDisconnected(HAMConnection *connection, const QString &reason);

	private slots:

		void handleDXClusterDoubleClicked(QTreeWidgetItem *item, int col);
		void handleEarthLocationChanged(double lat, double lon, double radius);

	private:
		int findColumnWithName(const std::string &name);

		Ui_MainWindow ui;
		QtEventLoop *m_eventLoop;
		HAMConnection *m_conn;
		bool m_register;
		bool m_refetch;
		bool m_askDXCC;
		ConnectDialog *m_connectDialog;
};
