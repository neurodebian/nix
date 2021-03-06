// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include <nix/hydra/multiArray.hpp>
#include <nix.hpp>
#include <nix/util/dataAccess.hpp>

#include <iostream>
#include <sstream>
#include <iterator>
#include <stdexcept>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>


class TestDataAccess: public CPPUNIT_NS::TestFixture {
private:

    CPPUNIT_TEST_SUITE(TestDataAccess);
    CPPUNIT_TEST(testPositionToIndexSampledDimension);
    CPPUNIT_TEST(testPositionToIndexSetDimension);
    CPPUNIT_TEST(testPositionToIndexRangeDimension);
    CPPUNIT_TEST(testOffsetAndCount);
    CPPUNIT_TEST(testPositionInData);
    CPPUNIT_TEST(testRetrieveData);
    CPPUNIT_TEST(testTagFeatureData);
    CPPUNIT_TEST(testMultiTagFeatureData);
    CPPUNIT_TEST(testMultiTagUnitSupport);
    CPPUNIT_TEST(testDataView);
    CPPUNIT_TEST_SUITE_END ();

    nix::File file;
    nix::DataArray data_array, alias_array;
    nix::Tag position_tag, segment_tag, times_tag;
    nix::MultiTag multi_tag;
    nix::Block block;
    nix::SampledDimension sampledDim;
    nix::RangeDimension rangeDim, aliasDim;
    nix::SetDimension setDim;

public:
    void setUp();
    void tearDown();
    void testPositionToIndexSetDimension();
    void testPositionToIndexSampledDimension();
    void testPositionToIndexRangeDimension();
    void testOffsetAndCount();
    void testPositionInData();
    void testRetrieveData();
    void testTagFeatureData();
    void testMultiTagFeatureData();
    void testMultiTagUnitSupport();
    void testDataView();
};

