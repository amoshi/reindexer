#include "ttlindex.h"

namespace reindexer {

template <typename T>
TtlIndex<T>::TtlIndex(const IndexDef &idef, const PayloadType payloadType, const FieldsSet &fields)
	: IndexOrdered<T>(idef, payloadType, fields), expireAfter_(idef.expireAfter_) {}

template <typename T>
int64_t TtlIndex<T>::GetTTLValue() const {
	return expireAfter_;
}

Index *TtlIndex_New(const IndexDef &idef, const PayloadType payloadType, const FieldsSet &fields) {
	if (idef.opts_.IsPK() || idef.opts_.IsDense()) {
		return new TtlIndex<btree_map<int64_t, Index::KeyEntryPlain>>(idef, payloadType, fields);
	}
	return new TtlIndex<btree_map<int64_t, Index::KeyEntry>>(idef, payloadType, fields);
}

template class TtlIndex<btree_map<int64_t, Index::KeyEntry>>;
template class TtlIndex<btree_map<int64_t, Index::KeyEntryPlain>>;

}  // namespace reindexer
