#include <pandora/SectionIterator.hpp>
#include <iostream>
#include <cstring>

using namespace std;

namespace pandora {


SectionIterator::SectionIterator(File file, Group group, std::string parent_id)
: file(file), group(group), parent(parent_id)
{
  index = 0;
  size  = group.objectCount();
  index = nextIndex(0);
}

SectionIterator::SectionIterator(const SectionIterator &other)
: file(other.file), group(other.group), index(other.index), size(other.size),parent(other.parent)
{
}

SectionIterator &SectionIterator::operator++() {
  index = nextIndex(index+1);
  return *this;
}

SectionIterator SectionIterator::begin() const {
  SectionIterator iter(*this);
  iter.index = 0;
  return iter;
}

SectionIterator SectionIterator::end() const {
  SectionIterator iter(*this);
  iter.index = size;
  return iter;
}

size_t SectionIterator::nextIndex(size_t start){
  size_t idx = size;
  for(size_t i = start; i < size; i++){
      std::string name = group.objectName(i);
      Group g = group.openGroup(name);
      std::string value;
      bool hasParent = g.hasAttr("parent");
      if(hasParent){
        g.getAttr("parent",value);
      }
      if(parent.length() == 0 && !hasParent){
        idx = i;
        break;
      }
      if(parent.length() == 0 && hasParent && value.length() == 0){
          idx = i;
          break;
      }
      if(parent.length() > 0 && value.length() > 0){
        if(value.compare(parent) == 0){
          idx = i;
          break;
        }
      }
    }
  return idx;
}


Section SectionIterator::operator*() const {
  string id;
  if (index  < size) {
    id = group.objectName(index);
  } else {
    id = group.objectName(size - 1);
  }
  Section section(file, group.openGroup(id, false), id);
  return section;
}

void SectionIterator::operator=(const SectionIterator &other) {
  file  = other.file;
  group = other.group;
  index = other.index;
  size  = other.size;
}

bool SectionIterator::operator==(const SectionIterator &other) const {
  return group == other.group && index == other.index;
}

bool SectionIterator::operator!=(const SectionIterator &other) const {
  return group != other.group || index != other.index;
}




} /* namespace pandora */