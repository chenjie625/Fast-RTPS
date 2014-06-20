/*************************************************************************
 * Copyright (c) 2014 eProsima. All rights reserved.
 *
 * This copy of eProsima RTPS is licensed to you under the terms described in the
 * EPROSIMARTPS_LIBRARY_LICENSE file included in this distribution.
 *
 *************************************************************************/

/**
 * @file WriterProxyLiveliness.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: Gonzalo Rodriguez Canosa
 *      email:  gonzalorodriguez@eprosima.com
 *              grcanosa@gmail.com  	
 */

#include "eprosimartps/reader/timedevent/WriterProxyLiveliness.h"
#include "eprosimartps/reader/StatefulReader.h"
#include "eprosimartps/reader/WriterProxy.h"
#include "eprosimartps/resources/ResourceEvent.h"
#include "eprosimartps/utils/RTPSLog.h"



namespace eprosima {
namespace rtps {

WriterProxyLiveliness::WriterProxyLiveliness(WriterProxy* wp,boost::posix_time::milliseconds interval):
				TimedEvent(&wp->mp_SFR->mp_event_thr->io_service,interval),
				mp_WP(wp)
{
	// TODO Auto-generated constructor stub
	cout <<" WriterProxy Liveliness created " << mp_WP->param.remoteWriterGuid <<" "<< interval<<endl;
}

WriterProxyLiveliness::~WriterProxyLiveliness()
{
	timer->cancel();
	delete(timer);
}

void WriterProxyLiveliness::event(const boost::system::error_code& ec)
{
	m_isWaiting = false;
	if(ec == boost::system::errc::success)
	{
		cout <<" WriterProxy Liveliness checking " << mp_WP->param.remoteWriterGuid <<" "<< this->getIntervalMsec()<<endl;
		pDebugInfo(MAGENTA<<"WriterProxyLiveliness: checking Writer: "<<mp_WP->param.remoteWriterGuid<<DEF<<endl;);
		if(!mp_WP->checkLiveliness())
		{
			pWarning("WriterProxyLiveliness failed, leaseDuration was "<< this->getIntervalMsec()<< " ms"<< endl;);
			mp_WP->mp_SFR->matched_writer_remove(mp_WP->param.remoteWriterGuid);
			return;
		}
		this->restart_timer();
	}
	else if(ec==boost::asio::error::operation_aborted)
	{
		pInfo("WriterProxyLiveliness aborted"<<endl);
	}
	else
	{
		pDebugInfo("WriterProxyLiveliness boost message: " <<ec.message()<<endl);
	}
}



} /* namespace rtps */
} /* namespace eprosima */
