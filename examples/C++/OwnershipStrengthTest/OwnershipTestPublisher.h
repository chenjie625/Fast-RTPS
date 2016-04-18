/*************************************************************************
 * Copyright (c) 2013 eProsima. All rights reserved.
 *
 * This generated file is licensed to you under the terms described in the
 * fastcdr_LICENSE file included in this fastcdr distribution.
 *
 *************************************************************************
 * 
 * @file OwnershipTestPublisher.h
 * This header file contains the declaration of the publisher functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#ifndef _OWNERSHIPTEST_PUBLISHER_H_
#define _OWNERSHIPTEST_PUBLISHER_H_

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/publisher/PublisherListener.h>

#include "OwnershipTestPubSubTypes.h"

using namespace eprosima::fastrtps;

class OwnershipTestPublisher 
{
public:
	OwnershipTestPublisher();
	virtual ~OwnershipTestPublisher();
	bool init();
	void run();
   void setOwnershipStrength(unsigned int strength);

private:
	Participant *mp_participant;
	Publisher *mp_publisher;
	
	class PubListener : public PublisherListener
	{
	public:
		PubListener() : n_matched(0){};
		~PubListener(){};
		void onPublicationMatched(Publisher* pub,MatchingInfo& info);
		int n_matched;
	} m_listener;
	ExampleMessagePubSubType myType;

   unsigned int m_strength;
   unsigned int m_messagesSent;

   static const unsigned int DefaultStrength = 10;
};

#endif // _OWNERSHIPTEST_PUBLISHER_H_
