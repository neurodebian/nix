// Copyright (c) 2013, German Neuroinformatics Node (G-Node)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted under the terms of the BSD License. See
// LICENSE file in the root of the Project.

#include <nix/Tag.hpp>

#include <nix/util/util.hpp>
#include <nix/util/dataAccess.hpp>


using namespace std;
using namespace nix;


void Tag::units(const std::vector<std::string> &units) {
    std::vector<std::string> sanitized;
    sanitized.reserve(units.size());
    std::transform(begin(units), end(units), std::back_inserter(sanitized), [](const std::string &x) {
        std::string unit = util::unitSanitizer(x);
        if (unit.length() > 0 && (unit != "none" && !(util::isSIUnit(unit)))) {
            std::string msg = "Unit " + unit +" is not a SI unit. Note: so far only atomic SI units are supported.";
            throw InvalidUnit(msg, "Tag::units(vector<string> &units)");
        }
        return unit;
    });
    backend()->units(sanitized);
}


bool Tag::hasReference(const DataArray &reference) const {
    util::checkEntityInput(reference);
    return backend()->hasReference(reference.id());
}


DataArray Tag::getReference(size_t index) const {
    if(index >= backend()->referenceCount()) {
        throw OutOfBounds("No reference at given index", index);
    }
    return backend()->getReference(index);
}


void Tag::addReference(const DataArray &reference) {
    util::checkEntityInput(reference);
    backend()->addReference(reference.id());
}


void Tag::addReference(const std::string &id) {
    util::checkNameOrId(id);
    backend()->addReference(id);
}


bool Tag::removeReference(const DataArray &reference) {
    util::checkEntityInput(reference);
    return backend()->removeReference(reference.id());
}


std::vector<DataArray> Tag::references(const util::Filter<DataArray>::type &filter) const {
    auto f = [this] (size_t i) { return getReference(i); };
    return getEntities<DataArray>(f,
                                  referenceCount(),
                                  filter);
}


bool Tag::hasFeature(const Feature &feature) const {
    util::checkEntityInput(feature);
    return backend()->hasFeature(feature.id());
}


std::vector<Feature> Tag::features(const util::Filter<Feature>::type &filter) const {
    auto f = [this] (size_t i) { return getFeature(i); };
    return getEntities<Feature>(f,
                                featureCount(),
                                filter);
}


Feature Tag::getFeature(const std::string &id) const {
    util::checkNameOrId(id);
    return backend()->getFeature(id);
}


Feature Tag::getFeature(size_t index) const {
    if (index >= backend()->featureCount()) {
        throw OutOfBounds("No feature at given index", index);
    }
    return backend()->getFeature(index);
}


Feature Tag::createFeature(const DataArray &data, LinkType link_type) {
    util::checkEntityInput(data);
    return backend()->createFeature(data.id(), link_type);
}


bool Tag::deleteFeature(const Feature &feature) {
    util::checkEntityInput(feature);
    return backend()->deleteFeature(feature.id());
}


DataView Tag::retrieveData(size_t reference_index) const {
    return util::retrieveData(*this, reference_index);
}


DataView Tag::retrieveFeatureData(size_t feature_index) const {
    return util::retrieveFeatureData(*this, feature_index);
}


std::ostream &nix::operator<<(std::ostream &out, const Tag &ent) {
    out << "Tag: {name = " << ent.name();
    out << ", type = " << ent.type();
    out << ", id = " << ent.id() << "}";
    return out;
}