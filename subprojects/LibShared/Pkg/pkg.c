/*
* PKG extraction code based on
* Real-Package-Installer by LiEnby.
* https://silica.codes/Li/real-package-installer/src/branch/main
*/


#include "pkg.h"
#include "err.h"
#include "io.h"

// fake vita headers: 
//#include "sceNpDrmPackage.hpp"
#include "sceIo.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int decrypt_pkg(PKG_STATE* state, int offset, void* buffer, size_t bufferSize) {
	/*_sceNpDrmPackageDecrypt_opt decryptOption;
	decryptOption.offset = offset; 
	decryptOption.identifier = 0x8001;
	
	CHECK_ERROR(_sceNpDrmPackageDecrypt(buffer, bufferSize, &decryptOption));*/

	aes128_ctr_xor(&state->pkgKey, state->pkgHeader.pkg_data_iv, offset / 16, buffer, bufferSize);

	return 0;
}


uint64_t seek_pkg(PKG_STATE* state, uint64_t whence, int mode) {
	SceOff newLocation = sceIoLseek(state->fd, whence, mode);
	CHECK_ERROR(newLocation);
	state->offset = newLocation;
	return newLocation;
}

int read_pkg(PKG_STATE* state, void* buffer, size_t bufferSize) {
	int amtRead = sceIoRead(state->fd, buffer, bufferSize);
	CHECK_ERROR(amtRead);
	
	if(state->offset >= state->pkgHeader.data_offset) {
		uint32_t relOffset = (state->offset - state->pkgHeader.data_offset);
		CHECK_ERROR(decrypt_pkg(state, relOffset, buffer, bufferSize));
	}
	
	state->offset += amtRead;
	return amtRead;
}

int read_pkg_offset(PKG_STATE* state, uint32_t offset, void* buffer, size_t bufferSize) {
	
	CHECK_ERROR(seek_pkg(state, offset, SCE_SEEK_SET));
	int amtRead = read_pkg(state, buffer, bufferSize);
	CHECK_ERROR(amtRead);
	
	return amtRead;
}

int pkg_get_metadata(PKG_STATE *state) {	
	CHECK_ERROR(seek_pkg(state, state->pkgHeader.meta_offset, SCE_SEEK_SET));
	
	
	for(int i = 0; i < state->pkgHeader.meta_count; i++) {
		PKG_METADATA_ENTRY metaEntry;
		CHECK_ERROR(read_pkg(state, &metaEntry, sizeof(PKG_METADATA_ENTRY)));
		
		metaEntry.type = __builtin_bswap32(metaEntry.type);
		metaEntry.size = __builtin_bswap32(metaEntry.size);
		int rd = 0;
				
		switch(metaEntry.type) {
			case PKG_META_DRM_TYPE:
				rd += read_pkg(state, &state->pkgMetadata.drm_type, sizeof(uint32_t));
				break;
			case PKG_META_CONTENT_TYPE:
				rd += read_pkg(state, &state->pkgMetadata.content_type, sizeof(uint32_t));
				break;
			case PKG_META_PACKAGE_FLAGS:
				rd += read_pkg(state, &state->pkgMetadata.package_flags, sizeof(uint32_t));
				break;
			case PKG_META_FILE_ITEM_INFO:
				rd += read_pkg(state, &state->pkgMetadata.item_table_offset, sizeof(uint32_t));
				rd += read_pkg(state, &state->pkgMetadata.item_table_size, sizeof(uint32_t));
				break;
			case PKG_META_SFO:
				rd += read_pkg(state, &state->pkgMetadata.sfo_offset, sizeof(uint32_t));
				rd += read_pkg(state, &state->pkgMetadata.sfo_size, sizeof(uint32_t));
				break;
			default:
				break;
		}
		CHECK_ERROR(rd);
		CHECK_ERROR(seek_pkg(state, metaEntry.size - rd, SCE_SEEK_CUR));
	}
	state->pkgMetadata.drm_type           = __builtin_bswap32( state->pkgMetadata.drm_type );
	state->pkgMetadata.content_type       = __builtin_bswap32( state->pkgMetadata.content_type );
	state->pkgMetadata.package_flags      = __builtin_bswap32( state->pkgMetadata.package_flags );
	state->pkgMetadata.item_table_offset  = __builtin_bswap32( state->pkgMetadata.item_table_offset);
	state->pkgMetadata.item_table_size    = __builtin_bswap32( state->pkgMetadata.item_table_size);
	state->pkgMetadata.sfo_offset         = __builtin_bswap32( state->pkgMetadata.sfo_offset );
	state->pkgMetadata.sfo_size           = __builtin_bswap32( state->pkgMetadata.sfo_size );
		
	return 0;
}

int close_pkg(PKG_STATE* state) {
	CHECK_ERROR(sceIoClose(state->fd));
	
	// clear state variables
	state->fd = 0;
	state->offset = 0;
	memset(&state->pkgItem, 0, sizeof(PKG_ITEM_RECORD));
	
	return 0;
}


int open_pkg(PKG_STATE* state, const char* pkg_file) {
	static char checkPkg[0x8000];
	memset(checkPkg, 0, sizeof(checkPkg));
	memset(state, 0, sizeof(PKG_STATE));
	
	state->fd = sceIoOpen(pkg_file, SCE_O_RDONLY, 0);
	CHECK_ERROR(state->fd);	
	
	// Removed because no NpDrmPackage on other devices;
	// check pkg with npdrm ...
	// CHECK_ERROR(sceIoRead(state->fd, checkPkg, sizeof(checkPkg)));
	// CHECK_ERROR(_sceNpDrmPackageCheck(checkPkg, sizeof(checkPkg), 0, 0x101));
	// CHECK_ERROR(sceIoLseek(state->fd, 0, SCE_SEEK_SET));
	
	CHECK_ERROR(sceIoRead(state->fd, &state->pkgHeader, sizeof(PKG_FILE_HEADER)));

	state->pkgHeader.magic       = __builtin_bswap32( state->pkgHeader.magic );
	state->pkgHeader.revision    = __builtin_bswap16( state->pkgHeader.revision );
	state->pkgHeader.type        = __builtin_bswap16( state->pkgHeader.type );
	state->pkgHeader.meta_offset = __builtin_bswap32( state->pkgHeader.meta_offset );
	state->pkgHeader.meta_count  = __builtin_bswap32( state->pkgHeader.meta_count );
	state->pkgHeader.meta_size   = __builtin_bswap32( state->pkgHeader.meta_size );
	state->pkgHeader.item_count  = __builtin_bswap32( state->pkgHeader.item_count );
	state->pkgHeader.total_size  = __builtin_bswap64( state->pkgHeader.total_size );
	state->pkgHeader.data_offset = __builtin_bswap64( state->pkgHeader.data_offset );
	state->pkgHeader.data_size   = __builtin_bswap64( state->pkgHeader.data_size );
		
	
	if (state->pkgHeader.type >= 2) {
		CHECK_ERROR(sceIoRead(state->fd, &state->pkgExtHeader, sizeof(PKG_EXT_HEADER)));
		
		state->pkgExtHeader.magic         =    __builtin_bswap32( state->pkgExtHeader.magic );
        state->pkgExtHeader.unknown_01    =    __builtin_bswap32( state->pkgExtHeader.unknown_01 );
        state->pkgExtHeader.header_size   =    __builtin_bswap32( state->pkgExtHeader.header_size );
        state->pkgExtHeader.data_size     =    __builtin_bswap32( state->pkgExtHeader.data_size );
        state->pkgExtHeader.data_offset   =    __builtin_bswap32( state->pkgExtHeader.data_offset );
        state->pkgExtHeader.data_type     =    __builtin_bswap32( state->pkgExtHeader.data_type );
        state->pkgExtHeader.pkg_data_size =    __builtin_bswap64( state->pkgExtHeader.pkg_data_size );
        state->pkgExtHeader.padding_01    =    __builtin_bswap32( state->pkgExtHeader.padding_01 );
        state->pkgExtHeader.data_type2    =    __builtin_bswap32( state->pkgExtHeader.data_type2 );
        state->pkgExtHeader.unknown_02    =    __builtin_bswap32( state->pkgExtHeader.unknown_02 );
        state->pkgExtHeader.padding_02    =    __builtin_bswap32( state->pkgExtHeader.padding_02 );
        state->pkgExtHeader.padding_03    =    __builtin_bswap64( state->pkgExtHeader.padding_03 );
        state->pkgExtHeader.padding_04    =    __builtin_bswap64( state->pkgExtHeader.padding_04 );
		
	}

	if (state->pkgHeader.magic != 0x7F504B47u || state->pkgExtHeader.magic != 0x7F657874u) CHECK_ERROR(-1);

	CHECK_ERROR(pkg_get_metadata(state));


	// because we don't have sceNpDrmPackage on anything except the Vita;
	// we have to do this part ourselves,

	uint8_t main_key[sizeof(state->pkgHeader.pkg_data_iv)];
	memcpy(main_key, state->pkgHeader.pkg_data_iv, sizeof(main_key));

	if (IS_PSM_CONTENT_TYPE(state->pkgMetadata.content_type)) {
		int keyId = state->pkgExtHeader.data_type2 & 0x7;
		if (keyId == PKG_KEYID_PSM) {
			aes128_key key;

			// decrypt the package key.
			aes128_init(&key, PKG_DECRYPT_KEY_PSM);
			aes128_ecb_encrypt(&key, main_key, sizeof(main_key));

			// setup package decrypt key.
			aes128_init(&state->pkgKey, main_key);
		}
		else {
			CHECK_ERROR(-3);
		}
	}
	else {
		CHECK_ERROR(-2);
	}

	return 0;
}

int extract_file(PKG_STATE* state, const char* outfile) {
	CHECK_ERROR(seek_pkg(state, state->pkgHeader.data_offset + state->pkgItem.data_offset, SCE_SEEK_SET));	
	SceUID wfd = sceIoOpen(outfile, SCE_O_WRONLY | SCE_O_CREAT, 0777);
	CHECK_ERROR(wfd);
	
	int ret = 0;
	static char buffer[0x8000];
	int totalRead = 0;
	
	do { 
		// get amount of data to read
		int readSize = (sizeof(buffer) < (state->pkgItem.data_size - totalRead)) ? sizeof(buffer) : (state->pkgItem.data_size - totalRead);
		
		// read the data
		int amtRead = read_pkg(state, buffer, readSize);
		if(amtRead < 0) ERROR(amtRead);
		if(amtRead != readSize) ERROR(-1);

		// write decrypted data
		int amtWritten = sceIoWrite(wfd, buffer, amtRead);
		if(amtWritten < 0) ERROR(amtWritten);
		if(amtWritten != amtRead) ERROR(-1);
		
		totalRead += amtWritten;

	} while(totalRead < state->pkgItem.data_size);

error:
	sceIoClose(wfd);
	return ret;
}

int expand_package(const char* pkg_file, const char* out_folder, void (*progress_callback)(const char*, uint64_t, uint64_t)) {
	
	char relFilename[MAX_PATH];
	char outfile[MAX_PATH*2];
	char dirname[MAX_PATH*2];
	
	PKG_STATE state;
	
	if(progress_callback != NULL) progress_callback(pkg_file, (uint64_t)0, (uint64_t)100);
	
	make_directories(out_folder);
	CHECK_ERROR(open_pkg(&state, pkg_file));
	
	extract_dirname(out_folder, dirname, sizeof(dirname));
	make_directories(dirname);

	
	for(int current_item = 0; current_item < state.pkgHeader.item_count; current_item++) 
	{
		memset(relFilename, 0, sizeof(relFilename));
		memset(outfile, 0, sizeof(outfile));
		
		// update progress in GUI
		if(progress_callback != NULL) progress_callback(pkg_file, (uint64_t)current_item, (uint64_t)state.pkgHeader.item_count);

		// read item record entry
		CHECK_ERROR(read_pkg_offset(&state, ((state.pkgHeader.data_offset + state.pkgMetadata.item_table_offset) + (current_item * sizeof(PKG_ITEM_RECORD))), &state.pkgItem, sizeof(PKG_ITEM_RECORD)));
		
		state.pkgItem.flags            = __builtin_bswap32(state.pkgItem.flags);
		state.pkgItem.filename_offset  = __builtin_bswap32(state.pkgItem.filename_offset);
		state.pkgItem.filename_size    = __builtin_bswap32(state.pkgItem.filename_size);
		state.pkgItem.data_offset      = __builtin_bswap64(state.pkgItem.data_offset);
		state.pkgItem.data_size        = __builtin_bswap64(state.pkgItem.data_size);	


		// read and item filename
		if(IS_PSP_CONTENT_TYPE(state.pkgMetadata.content_type) && !IS_PSP_OR_VITA_KEY(state.pkgItem.flags)) continue; // vita cant decrypt ps3 encrypted items.
		if(state.pkgItem.filename_size > sizeof(relFilename)) CHECK_ERROR(-3);
		CHECK_ERROR(read_pkg_offset(&state, (state.pkgHeader.data_offset + state.pkgItem.filename_offset), relFilename, state.pkgItem.filename_size));	
		snprintf(outfile, sizeof(outfile), "%s/%s", out_folder, relFilename);
		
		// create directories for it.
		extract_dirname(outfile, dirname, sizeof(dirname));
		make_directories(dirname);
		
		switch(state.pkgItem.flags & 0x1F){
			case PKG_TYPE_FILE:
			case PKG_TYPE_SELF:
			case PKG_TYPE_PFS_KEYSTONE:
			case PKG_TYPE_PFS_FILE:
			case PKG_TYPE_PFS_TEMP_BIN:
			case PKG_TYPE_PFS_CLEARSIGN:
			case PKG_TYPE_SCESYS_RIGHT_SUPRX:
			default:
				CHECK_ERROR(extract_file(&state, outfile));
				break;
			case PKG_TYPE_DIR:
			case PKG_TYPE_PFS_DIR:
				make_directories(outfile);
				break;
			case PKG_TYPE_SCESYS_CERT_BIN:
			case PKG_TYPE_SCESYS_DIGS_BIN:
				// ignore these ..
				break;
		}

	}
	
	// create head.bin
	snprintf(outfile, sizeof(outfile), "%s/%s", out_folder, "sce_sys/package/head.bin");
	get_head_bin(&state, outfile);

	// create tail.bin
	snprintf(outfile, sizeof(outfile), "%s/%s", out_folder, "sce_sys/package/tail.bin");
	get_tail_bin(&state, outfile);

	// create work.bin (if appliciable)
	snprintf(outfile, sizeof(outfile), "%s/%s", out_folder, "sce_sys/package/work.bin");	
	get_work_bin(&state, out_folder, outfile);
	
	close_pkg(&state);
	return 0;
}



PKG_STATE package_state(const char* pkg_file) {
	PKG_STATE state;
	
	int res = open_pkg(&state, pkg_file);
	if(res > 0) close_pkg(&state);
	
	return state;
}

void package_content_id(const char* pkg_file, char* content_id, size_t len) {
	PKG_STATE state = package_state(pkg_file);
	if(len > sizeof(state.pkgHeader.content_id)) len = sizeof(state.pkgHeader.content_id);
	strncpy(content_id, state.pkgHeader.content_id, len);
}

int package_meta_flags(const char* pkg_file) {	
	return package_state(pkg_file).pkgMetadata.package_flags;
}

int package_content_type(const char* pkg_file) {	
	return package_state(pkg_file).pkgMetadata.content_type;
}

int package_revision(const char* pkg_file) {
	return package_state(pkg_file).pkgHeader.revision;
}

int get_work_bin(PKG_STATE* state, const char* pkg_folder, const char* outfile) {
	return 0; // not needed;

	char tempBinPath[MAX_PATH];
	snprintf(tempBinPath, sizeof(tempBinPath), "%s/%s", pkg_folder, "sce_sys/package/temp.bin");

	if(file_exist(tempBinPath)) {
		uint64_t rifSize = get_file_size(tempBinPath);
		
		return (copy_file(tempBinPath, outfile) >= 0);

	}
	
	return 0;
}

int get_head_bin(PKG_STATE* state, const char* outfile) {
	int ret = 0;
	int headSize = (state->pkgHeader.data_offset + state->pkgMetadata.item_table_size);
	char* head = malloc(headSize);
	
	if(head != NULL) {
		if(sceIoLseek(state->fd, 0, SCE_SEEK_SET) != 0) ERROR(-99);
		if(sceIoRead(state->fd, head, headSize) != headSize) ERROR(-99);
		if(write_file(outfile, head, headSize) != headSize) ERROR(-99);		
	}
	else {
		ERROR(0);
	}
	

error:
	seek_pkg(state, 0, SCE_SEEK_SET);
	free(head);
	return ret;
}

int get_tail_bin(PKG_STATE* state, const char* outfile) {
	
	int ret = 0;
	uint64_t tailOffset = state->pkgHeader.data_offset + state->pkgHeader.data_size;
	int tailSize = state->pkgHeader.total_size - tailOffset;
	char* tail = malloc(tailSize);
	
	if(tail != NULL) {
		if(sceIoLseek(state->fd, tailOffset, SCE_SEEK_SET) != tailOffset) ERROR(-99);
		if(sceIoRead(state->fd, tail, tailSize) != tailSize) ERROR(-99);
		if(write_file(outfile, tail, tailSize) != tailSize) ERROR(-99);
	}
	else {
		ERROR(0);
	}
	
error:
	seek_pkg(state, 0, SCE_SEEK_SET);
	free(tail);
	return ret;
}
