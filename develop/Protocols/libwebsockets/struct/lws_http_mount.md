[原文链接](https://libwebsockets.org/lws-api-doc-main/html/structlws__http__mount.html)

	/** struct lws_http_mount
	 *
	 * arguments for mounting something in a vhost's url namespace
	 */
	struct lws_http_mount {
		const struct lws_http_mount *mount_next;
						/**< pointer to next struct lws_http_mount */
		const char *mountpoint;
						/**< mountpoint in http pathspace, eg, "/" */
		const char *origin;
						/**< path to be mounted, eg, "/var/www/warmcat.com" */
		const char *def;
						/**< default target, eg, "index.html" */
		const char *protocol;
						/**<"protocol-name" to handle mount */

		const struct lws_protocol_vhost_options *cgienv;
						/**< optional linked-list of cgi options.  These are created
						 * as environment variables for the cgi process
						 */
		const struct lws_protocol_vhost_options *extra_mimetypes;
						/**< optional linked-list of mimetype mappings */
		const struct lws_protocol_vhost_options *interpret;
						/**< optional linked-list of files to be interpreted */

		int cgi_timeout;
						/**< seconds cgi is allowed to live, if cgi://mount type */
		int cache_max_age;
						/**< max-age for reuse of client cache of files, seconds */
		unsigned int auth_mask;
						/**< bits set here must be set for authorized client session */

		unsigned int cache_reusable:1;
						/**< set if client cache may reuse this */
		unsigned int cache_revalidate:1;
						/**< set if client cache should revalidate on use */
		unsigned int cache_intermediaries:1;
						/**< set if intermediaries are allowed to cache */
		unsigned int cache_no:1;
						/**< set if client should check cache always*/

		unsigned char origin_protocol; 		/**< one of enum lws_mount_protocols */
		unsigned char mountpoint_len; 		/**< length of mountpoint string */

		const char *basic_auth_login_file;
				/**<NULL, or filepath to use to check basic auth logins against. (requires LWSAUTHM_DEFAULT) */

				/* Add new things just above here ---^
				 * This is part of the ABI, don't needlessly break compatibility
				 */
	};