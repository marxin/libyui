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

  File:		YQPkgRepoFilterView.cc

  Author:	Stefan Hundhammer <sh@suse.de>

  Textdomain	"qt-pkg"

/-*/


#define YUILogComponent "qt-pkg"
#include "YUILog.h"

#include <qsplitter.h>

#include "QY2ComboTabWidget.h"
#include "QY2LayoutUtils.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include "YQPkgRepoFilterView.h"
#include "YQPkgRepoList.h"
#include "YQPkgRpmGroupTagsFilterView.h"
#include "YQPkgSearchFilterView.h"
#include "YQPkgStatusFilterView.h"
#include "YQi18n.h"

#define MARGIN			4


YQPkgRepoFilterView::YQPkgRepoFilterView( QWidget * parent )
    : QWidget( parent )
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    QSplitter * splitter = new QSplitter( Qt::Vertical, this );
    Q_CHECK_PTR( splitter );

    layout->addWidget( splitter );

    //QVBoxLayout * upper_vbox = new QVBoxLayout( splitter );
    
    _repoList = new YQPkgRepoList( this );
    //upper_vbox->addWidget(_repoList);
    splitter->addWidget(_repoList);
    
    Q_CHECK_PTR( _repoList );
    _repoList->setSizePolicy( QSizePolicy( QSizePolicy::Ignored, QSizePolicy::Expanding ) );// hor/vert

    //addVSpacing( upper_vbox, MARGIN );


    // Directly propagate signals filterStart() and filterFinished()
    // from primary filter to the outside

    connect( _repoList,	SIGNAL( filterStart() ),
	     this,		SIGNAL( filterStart() ) );

    connect( _repoList,	SIGNAL( filterFinished() ),
	     this, 		SIGNAL( filterFinished() ) );


    // Redirect filterMatch() and filterNearMatch() signals to secondary filter

    connect( _repoList,	SIGNAL( filterMatch		( ZyppSel, ZyppPkg ) ),
	     this,		SLOT  ( primaryFilterMatch	( ZyppSel, ZyppPkg ) ) );

    connect( _repoList,	SIGNAL( filterNearMatch		( ZyppSel, ZyppPkg ) ),
	     this,		SLOT  ( primaryFilterNearMatch	( ZyppSel, ZyppPkg ) ) );

#if 0
    QWidget * secondary_filters =
#endif
    layoutSecondaryFilters( splitter );

#if 0
    splitter->setResizeMode( _repoList,	QSplitter::Stretch        );
    splitter->setResizeMode( secondary_filters, QSplitter::FollowSizeHint );
#endif
}


YQPkgRepoFilterView::~YQPkgRepoFilterView()
{
    // NOP
}


QWidget *
YQPkgRepoFilterView::layoutSecondaryFilters( QWidget * parent )
{
    QWidget *vbox = new QWidget(parent);
    Q_CHECK_PTR( vbox );

    QVBoxLayout *layout = new QVBoxLayout();
    vbox->setLayout(layout);
    
    layout->addSpacing( MARGIN );

    // Translators: This is a combo box where the user can apply a secondary filter
    // in addition to the primary filter by repository - one of
    // "All packages", "RPM groups", "search", "summary"
    //
    // And yes, the colon really belongs there since this is one of the very
    // few cases where a combo box label is left to the combo box rather than
    // above it.
    _secondaryFilters = new QY2ComboTabWidget( _( "&Secondary Filter:" ));
    layout->addWidget(_secondaryFilters);

    Q_CHECK_PTR( _secondaryFilters );

//     _secondaryFilters->setFrameStyle( Q3Frame::Plain );
//     _secondaryFilters->setLineWidth( 0 );
//     _secondaryFilters->setMidLineWidth( 0 );
//     _secondaryFilters->setMargin( 0 );


    //
    // All Packages
    //

    _allPackages = new QWidget( this );
    layout->addWidget(_allPackages);
    Q_CHECK_PTR( _allPackages );
    _secondaryFilters->addPage( _( "All Packages" ), _allPackages );

    // unmaintaned packages (packages that are not provided in any of
    // the configured repositories)
    
    _unmaintainedPackages = new QWidget( this );
    layout->addWidget(_unmaintainedPackages);
    Q_CHECK_PTR( _unmaintainedPackages );
    _secondaryFilters->addPage( _( "Unmaintained Packages" ), _unmaintainedPackages );

    //
    // RPM Groups
    //

    _rpmGroupTagsFilterView = new YQPkgRpmGroupTagsFilterView( this );
    layout->addWidget(_rpmGroupTagsFilterView);

    Q_CHECK_PTR( _rpmGroupTagsFilterView );
    _secondaryFilters->addPage( _( "Package Groups" ), _rpmGroupTagsFilterView );

    connect( _rpmGroupTagsFilterView,	SIGNAL( filterStart() ),
	     _repoList,		SLOT  ( filter()      ) );


    //
    // Package search view
    //

    _searchFilterView = new YQPkgSearchFilterView(this);
    layout->addWidget(_searchFilterView);
    Q_CHECK_PTR( _searchFilterView );
    _secondaryFilters->addPage( _( "Search" ), _searchFilterView );

    connect( _searchFilterView,	SIGNAL( filterStart() ),
	     _repoList,	SLOT  ( filter()      ) );

    connect( _secondaryFilters, SIGNAL( currentChanged( QWidget * ) ),
	     this, 		SLOT  ( filter()		  ) );


    //
    // Status change view
    //

    _statusFilterView = new YQPkgStatusFilterView( parent );
    Q_CHECK_PTR( _statusFilterView );
    _secondaryFilters->addPage( _( "Installation Summary" ), _statusFilterView );

    connect( _statusFilterView,	SIGNAL( filterStart() ),
	     _repoList,	SLOT  ( filter()      ) );


    return _secondaryFilters;
}


void YQPkgRepoFilterView::filter()
{
    _repoList->filter();
}


void YQPkgRepoFilterView::filterIfVisible()
{
    _repoList->filterIfVisible();
}


void YQPkgRepoFilterView::primaryFilterMatch( ZyppSel 	selectable,
						 ZyppPkg 	pkg )
{
    if ( secondaryFilterMatch( selectable, pkg ) )
	emit filterMatch( selectable, pkg );
}


void YQPkgRepoFilterView::primaryFilterNearMatch( ZyppSel	selectable,
						     ZyppPkg 	pkg )
{
    if ( secondaryFilterMatch( selectable, pkg ) )
	emit filterNearMatch( selectable, pkg );
}


bool
YQPkgRepoFilterView::secondaryFilterMatch( ZyppSel	selectable,
					      ZyppPkg 	pkg )
{
    if ( _allPackages->isVisible() )
    {
	return true;
    }
    else if ( _unmaintainedPackages->isVisible() )
    {
        return ( selectable->availableObjs() == 0 );
    }
    else if ( _rpmGroupTagsFilterView->isVisible() )
    {
	return _rpmGroupTagsFilterView->check( selectable, pkg );
    }
    else if ( _searchFilterView->isVisible() )
    {
	return _searchFilterView->check( selectable, pkg );
    }
    else if ( _statusFilterView->isVisible() )
    {
	return _statusFilterView->check( selectable, pkg );
    }
    else
    {
	return true;
    }
}






#include "YQPkgRepoFilterView.moc"
