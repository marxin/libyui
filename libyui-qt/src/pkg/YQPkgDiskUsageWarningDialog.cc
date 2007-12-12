/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:	      YQPkgDiskUsageWarningDialog.cc

  Author:     Stefan Hundhammer <sh@suse.de>

  Textdomain "packages-qt"

/-*/

#define y2log_component "qt-pkg"
#include <ycp/y2log.h>

#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QStyle>
#include <QBoxLayout>

#include "YQPkgDiskUsageWarningDialog.h"
#include "YQPkgDiskUsageList.h"
#include "QY2LayoutUtils.h"
#include "YQUI.h"
#include "YQi18n.h"


#define SPACING			2	// between subwidgets
#define MARGIN			4	// around the widget


YQPkgDiskUsageWarningDialog::YQPkgDiskUsageWarningDialog( QWidget *		parent,
							  const QString & 	message,
							  int			thresholdPercent,
							  const QString &	acceptButtonLabel,
							  const QString &	rejectButtonLabel )
    : QDialog( parent )
{
    // Dialog title
    setWindowTitle( _( "Disk Space Warning" ) );

    // Enable dialog resizing even without window manager
    setSizeGripEnabled( true );

    // Layout for the dialog ( can't simply insert a QVBox )

    QVBoxLayout * layout = new QVBoxLayout( this );
    layout->setSpacing( SPACING );
    layout->setMargin ( MARGIN  );
    Q_CHECK_PTR( layout );


    // HBox for icon and message
    QHBoxLayout * hbox = new QHBoxLayout( this );
    Q_CHECK_PTR( hbox );
    layout->addLayout( hbox );


    // Icon

    //addHSpacing( hbox );
    QLabel * iconLabel = new QLabel( this );
    Q_CHECK_PTR( iconLabel );
    hbox->addWidget(iconLabel);
#ifdef FIXME
    iconLabel->setPixmap( QApplication::style().stylePixmap( QStyle::SP_MessageBoxWarning ) );
#endif
    iconLabel->setSizePolicy( QSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum ) ); // hor/vert

    // Label for the message

    QLabel * label = new QLabel( message, this);
    Q_CHECK_PTR( label );
    hbox->addWidget(label);
    label->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum ) ); // hor/vert


    // Disk usage list

    YQPkgDiskUsageList * duList = new YQPkgDiskUsageList( this, thresholdPercent );
    Q_CHECK_PTR( duList );

    layout->addWidget( duList );


    // Button box

    hbox = new QHBoxLayout( this );
    Q_CHECK_PTR( hbox );
    hbox->setSpacing( SPACING );
    hbox->setMargin ( MARGIN  );
    layout->addLayout( hbox );

    //addHStretch( hbox );


    // Accept button - usually "OK" or "Continue"

    QPushButton * button = new QPushButton( acceptButtonLabel, this );
    Q_CHECK_PTR( button );
    hbox->addWidget(button);

    connect( button,	SIGNAL( clicked() ),
	     this,      SLOT  ( accept()  ) );

    //addHStretch( hbox );


    if ( ! rejectButtonLabel.isEmpty() )
    {
	// Reject button ( if desired ) - usually "Cancel"

	button = new QPushButton( rejectButtonLabel, this );
	Q_CHECK_PTR( button );
  hbox->addWidget(button);

	connect( button,	SIGNAL( clicked() ),
		 this,      	SLOT  ( reject()  ) );

	//addHStretch( hbox );
    }

    // If there is only one button, it's safe to make that one ( the accept
    // button ) the default. If there are two, better be safe than sorry and
    // make the reject button the default.

    button->setDefault( true );
}


bool
YQPkgDiskUsageWarningDialog::diskUsageWarning( const QString & 	message,
					       int		thresholdPercent,
					       const QString &	acceptButtonLabel,
					       const QString &	rejectButtonLabel )
{
    YQPkgDiskUsageWarningDialog dialog( 0,
					message,
					thresholdPercent,
					acceptButtonLabel,
					rejectButtonLabel );
    YQUI::ui()->normalCursor();
    dialog.exec();

    return dialog.result() == QDialog::Accepted;
}




#include "YQPkgDiskUsageWarningDialog.moc"
