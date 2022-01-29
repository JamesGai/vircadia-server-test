macro(define_external_asset_urls ASSETNAME)
    set(EXTERNAL_${ASSETNAME}_URLS "")

    set(EXTERNAL_${ASSETNAME}_IPFS_URLS "")
    foreach(f ${EXTERNAL_BUILD_ASSETS_IPFS_BASE_URLS})
        list(APPEND EXTERNAL_${ASSETNAME}_IPFS_URLS  "${f}/${EXTERNAL_${ASSETNAME}_IPFS_CID}")
    endforeach(f)

    set(EXTERNAL_${ASSETNAME}_DIRECT_URLS "")
    foreach(f ${EXTERNAL_BUILD_ASSETS_DIRECT_BASE_URLS})
        list(APPEND EXTERNAL_${ASSETNAME}_DIRECT_URLS  "${f}/${EXTERNAL_${ASSETNAME}_PATH}")
    endforeach(f)

    if (USE_IPFS_EXTERNAL_BUILD_ASSETS)
        list(APPEND EXTERNAL_${ASSETNAME}_URLS ${EXTERNAL_${ASSETNAME}_IPFS_URLS})
    endif()
    if (USE_DIRECT_EXTERNAL_BUILD_ASSETS)
        list(APPEND EXTERNAL_${ASSETNAME}_URLS ${EXTERNAL_${ASSETNAME}_DIRECT_URLS})
    endif()

    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/_env/EXTERNAL_${ASSETNAME}_URLS.txt" "${EXTERNAL_${ASSETNAME}_URLS}")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/_env/EXTERNAL_${ASSETNAME}_SHA512.txt" "${EXTERNAL_${ASSETNAME}_SHA512}")

endmacro(define_external_asset_urls)

