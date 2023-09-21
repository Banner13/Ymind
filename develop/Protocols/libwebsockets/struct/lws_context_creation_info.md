
	struct lws_context_creation_info {
	#if defined(LWS_WITH_NETWORK)
		const char *iface;
		/**< VHOST: NULL to bind the listen socket to all interfaces, or the
		 * interface name, eg, "eth2"
		 * If options specifies LWS_SERVER_OPTION_UNIX_SOCK, this member is
		 * the pathname of a UNIX domain socket. you can use the UNIX domain
		 * sockets in abstract namespace, by prepending an at symbol to the
		 * socket name. */
		const struct lws_protocols *protocols;
		/**< VHOST: Array of structures listing supported protocols and a
		 * protocol-specific callback for each one.  The list is ended with an
		 * entry that has a NULL callback pointer.  SEE ALSO .pprotocols below,
		 * which gives an alternative way to provide an array of pointers to
		 * protocol structs. */

	#if defined(LWS_ROLE_WS)
		const struct lws_extension *extensions;
		/**< VHOST: NULL or array of lws_extension structs listing the
		 * extensions this context supports. */
	#endif

	#if defined(LWS_ROLE_H1) || defined(LWS_ROLE_H2)
		const struct lws_token_limits *token_limits;
		/**< CONTEXT: NULL or struct lws_token_limits pointer which is
		 * initialized with a token length limit for each possible WSI_TOKEN_ */
		const char *http_proxy_address;
		/**< VHOST: If non-NULL, attempts to proxy via the given address.
		 * If proxy auth is required, use format
		 * "username:password\@server:port" */
		const struct lws_protocol_vhost_options *headers;
			/**< VHOST: pointer to optional linked list of per-vhost
			 * canned headers that are added to server responses */

		const struct lws_protocol_vhost_options *reject_service_keywords;
		/**< CONTEXT: Optional list of keywords and rejection codes + text.
		 *
		 * The keywords are checked for existing in the user agent string.
		 *
		 * Eg, "badrobot" "404 Not Found"
		 */
		const struct lws_protocol_vhost_options *pvo;
		/**< VHOST: pointer to optional linked list of per-vhost
		 * options made accessible to protocols */
		const char *log_filepath;
		/**< VHOST: filepath to append logs to... this is opened before
		 *		any dropping of initial privileges */
		const struct lws_http_mount *mounts;
		/**< VHOST: optional linked list of mounts for this vhost */
		const char *server_string;
		/**< CONTEXT: string used in HTTP headers to identify server
		 * software, if NULL, "libwebsockets". */

		const char *error_document_404;
		/**< VHOST: If non-NULL, when asked to serve a non-existent file,
		 *          lws attempts to server this url path instead.  Eg,
		 *          "/404.html" */
		int port;
		/**< VHOST: Port to listen on. Use CONTEXT_PORT_NO_LISTEN to suppress
		 * listening for a client. Use CONTEXT_PORT_NO_LISTEN_SERVER if you are
		 * writing a server but you are using \ref sock-adopt instead of the
		 * built-in listener.
		 *
		 * You can also set port to 0, in which case the kernel will pick
		 * a random port that is not already in use.  You can find out what
		 * port the vhost is listening on using lws_get_vhost_listen_port() */

		unsigned int http_proxy_port;
		/**< VHOST: If http_proxy_address was non-NULL, uses this port */
		unsigned int max_http_header_data2;
		/**< CONTEXT: if max_http_header_data is 0 and this
		 * is nonzero, this will be used in place of the default.  It's
		 * like this for compatibility with the original short version,
		 * this is unsigned int length. */
		unsigned int max_http_header_pool2;
		/**< CONTEXT: if max_http_header_pool is 0 and this
		 * is nonzero, this will be used in place of the default.  It's
		 * like this for compatibility with the original short version:
		 * this is unsigned int length. */

		int keepalive_timeout;
		/**< VHOST: (default = 0 = 5s, 31s for http/2) seconds to allow remote
		 * client to hold on to an idle HTTP/1.1 connection.  Timeout lifetime
		 * applied to idle h2 network connections */
		uint32_t	http2_settings[7];
		/**< VHOST:  if http2_settings[0] is nonzero, the values given in
		 *	      http2_settings[1]..[6] are used instead of the lws
		 *	      platform default values.
		 *	      Just leave all at 0 if you don't care.
		 */

		unsigned short max_http_header_data;
		/**< CONTEXT: The max amount of header payload that can be handled
		 * in an http request (unrecognized header payload is dropped) */
		unsigned short max_http_header_pool;
		/**< CONTEXT: The max number of connections with http headers that
		 * can be processed simultaneously (the corresponding memory is
		 * allocated and deallocated dynamically as needed).  If the pool is
		 * fully busy new incoming connections must wait for accept until one
		 * becomes free. 0 = allow as many ah as number of availble fds for
		 * the process */
	#endif

	#if defined(LWS_WITH_TLS)
		const char *ssl_private_key_password;
		/**< VHOST: NULL or the passphrase needed for the private key. (For
		 * backwards compatibility, this can also be used to pass the client
		 * cert passphrase when setting up a vhost client SSL context, but it is
		 * preferred to use .client_ssl_private_key_password for that.) */
		const char *ssl_cert_filepath;
		/**< VHOST: If libwebsockets was compiled to use ssl, and you want
		 * to listen using SSL, set to the filepath to fetch the
		 * server cert from, otherwise NULL for unencrypted.  (For backwards
		 * compatibility, this can also be used to pass the client certificate
		 * when setting up a vhost client SSL context, but it is preferred to
		 * use .client_ssl_cert_filepath for that.)
		 *
		 * Notice you can alternatively set a single DER or PEM from a memory
		 * buffer as the vhost tls cert using \p server_ssl_cert_mem and
		 * \p server_ssl_cert_mem_len.
		 */
		const char *ssl_private_key_filepath;
		/**<  VHOST: filepath to private key if wanting SSL mode;
		 * this should not be set to NULL when ssl_cert_filepath is set.
		 *
		 * Alteratively, the certificate and private key can both be set in
		 * the OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS callback directly via
		 * openSSL library calls.  This requires that
		 * LWS_SERVER_OPTION_CREATE_VHOST_SSL_CTX is set in the vhost info options
		 * to force initializtion of the SSL_CTX context.
		 *
		 * (For backwards compatibility, this can also be used
		 * to pass the client cert private key filepath when setting up a
		 * vhost client SSL context, but it is preferred to use
		 * .client_ssl_private_key_filepath for that.)
		 *
		 * Notice you can alternatively set a DER or PEM private key from a
		 * memory buffer as the vhost tls private key using
		 * \p server_ssl_private_key_mem and \p server_ssl_private_key_mem_len.
		 */
		const char *ssl_ca_filepath;
		/**< VHOST: CA certificate filepath or NULL.  (For backwards
		 * compatibility, this can also be used to pass the client CA
		 * filepath when setting up a vhost client SSL context,
		 * but it is preferred to use .client_ssl_ca_filepath for that.)
		 *
		 * Notice you can alternatively set a DER or PEM CA cert from a memory
		 * buffer using \p server_ssl_ca_mem and \p server_ssl_ca_mem_len.
		 */
		const char *ssl_cipher_list;
		/**< VHOST: List of valid ciphers to use ON TLS1.2 AND LOWER ONLY (eg,
		 * "RC4-MD5:RC4-SHA:AES128-SHA:AES256-SHA:HIGH:!DSS:!aNULL"
		 * or you can leave it as NULL to get "DEFAULT" (For backwards
		 * compatibility, this can also be used to pass the client cipher
		 * list when setting up a vhost client SSL context,
		 * but it is preferred to use .client_ssl_cipher_list for that.)
		 * SEE .tls1_3_plus_cipher_list and .client_tls_1_3_plus_cipher_list
		 * for the equivalent for tls1.3.
		 */
		const char *ecdh_curve;
		/**< VHOST: if NULL, defaults to initializing server with
		 *   "prime256v1" */
		const char *tls1_3_plus_cipher_list;
		/**< VHOST: List of valid ciphers to use for incoming server connections
		 * ON TLS1.3 AND ABOVE (eg, "TLS_CHACHA20_POLY1305_SHA256" on this vhost
		 * or you can leave it as NULL to get "DEFAULT".
		 * SEE .client_tls_1_3_plus_cipher_list to do the same on the vhost
		 * client SSL_CTX.
		 */

		const void *server_ssl_cert_mem;
		/**< VHOST: Alternative for \p ssl_cert_filepath that allows setting
		 * from memory instead of from a file.  At most one of
		 * \p ssl_cert_filepath or \p server_ssl_cert_mem should be non-NULL. */
		const void *server_ssl_private_key_mem;
		/**<  VHOST: Alternative for \p ssl_private_key_filepath allowing
		 * init from a private key in memory instead of a file.  At most one
		 * of \p ssl_private_key_filepath or \p server_ssl_private_key_mem
		 * should be non-NULL. */
		const void *server_ssl_ca_mem;
		/**< VHOST: Alternative for \p ssl_ca_filepath allowing
		 * init from a CA cert in memory instead of a file.  At most one
		 * of \p ssl_ca_filepath or \p server_ssl_ca_mem should be non-NULL. */

		long ssl_options_set;
		/**< VHOST: Any bits set here will be set as server SSL options */
		long ssl_options_clear;
		/**< VHOST: Any bits set here will be cleared as server SSL options */
		int simultaneous_ssl_restriction;
		/**< CONTEXT: 0 (no limit) or limit of simultaneous SSL sessions
		 * possible.*/
		int simultaneous_ssl_handshake_restriction;
		/**< CONTEXT: 0 (no limit) or limit of simultaneous SSL handshakes ongoing */
		int ssl_info_event_mask;
		/**< VHOST: mask of ssl events to be reported on LWS_CALLBACK_SSL_INFO
		 * callback for connections on this vhost.  The mask values are of
		 * the form SSL_CB_ALERT, defined in openssl/ssl.h.  The default of
		 * 0 means no info events will be reported.
		 */
		unsigned int server_ssl_cert_mem_len;
		/**< VHOST: Server SSL context init: length of server_ssl_cert_mem in
		 * bytes */
		unsigned int server_ssl_private_key_mem_len;
		/**< VHOST: length of \p server_ssl_private_key_mem in memory */
		unsigned int server_ssl_ca_mem_len;
		/**< VHOST: length of \p server_ssl_ca_mem in memory */

		const char *alpn;
		/**< CONTEXT: If non-NULL, default list of advertised alpn, comma-
		 *	      separated
		 *
		 *     VHOST: If non-NULL, per-vhost list of advertised alpn, comma-
		 *	      separated
		 */


	#if defined(LWS_WITH_CLIENT)
		const char *client_ssl_private_key_password;
		/**< VHOST: Client SSL context init: NULL or the passphrase needed
		 * for the private key */
		const char *client_ssl_cert_filepath;
		/**< VHOST: Client SSL context init: The certificate the client
		 * should present to the peer on connection */
		const void *client_ssl_cert_mem;
		/**< VHOST: Client SSL context init: client certificate memory buffer or
		 * NULL... use this to load client cert from memory instead of file */
		unsigned int client_ssl_cert_mem_len;
		/**< VHOST: Client SSL context init: length of client_ssl_cert_mem in
		 * bytes */
		const char *client_ssl_private_key_filepath;
		/**<  VHOST: Client SSL context init: filepath to client private key
		 * if this is set to NULL but client_ssl_cert_filepath is set, you
		 * can handle the LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS
		 * callback of protocols[0] to allow setting of the private key directly
		 * via tls library calls */
		const void *client_ssl_key_mem;
		/**< VHOST: Client SSL context init: client key memory buffer or
		 * NULL... use this to load client key from memory instead of file */
		const char *client_ssl_ca_filepath;
		/**< VHOST: Client SSL context init: CA certificate filepath or NULL */
		const void *client_ssl_ca_mem;
		/**< VHOST: Client SSL context init: CA certificate memory buffer or
		 * NULL... use this to load CA cert from memory instead of file */

		const char *client_ssl_cipher_list;
		/**< VHOST: Client SSL context init: List of valid ciphers to use (eg,
		* "RC4-MD5:RC4-SHA:AES128-SHA:AES256-SHA:HIGH:!DSS:!aNULL"
		* or you can leave it as NULL to get "DEFAULT" */
		const char *client_tls_1_3_plus_cipher_list;
		/**< VHOST: List of valid ciphers to use for outgoing client connections
		 * ON TLS1.3 AND ABOVE on this vhost (eg,
		 * "TLS_CHACHA20_POLY1305_SHA256") or you can leave it as NULL to get
		 * "DEFAULT".
		 */

		long ssl_client_options_set;
		/**< VHOST: Any bits set here will be set as CLIENT SSL options */
		long ssl_client_options_clear;
		/**< VHOST: Any bits set here will be cleared as CLIENT SSL options */


		unsigned int client_ssl_ca_mem_len;
		/**< VHOST: Client SSL context init: length of client_ssl_ca_mem in
		 * bytes */
		unsigned int client_ssl_key_mem_len;
		/**< VHOST: Client SSL context init: length of client_ssl_key_mem in
		 * bytes */
	#endif

	#if !defined(LWS_WITH_MBEDTLS)
		SSL_CTX *provided_client_ssl_ctx;
		/**< CONTEXT: If non-null, swap out libwebsockets ssl
		  * implementation for the one provided by provided_ssl_ctx.
		  * Libwebsockets no longer is responsible for freeing the context
		  * if this option is selected. */
	#else /* WITH_MBEDTLS */
		const char *mbedtls_client_preload_filepath;
		/**< CONTEXT: If NULL, no effect.  Otherwise it should point to a
		 * filepath where every created client SSL_CTX is preloaded from the
		 * system trust bundle.
		 *
		 * This sets a processwide variable that affects all contexts.
		 *
		 * Requires that the mbedtls provides mbedtls_x509_crt_parse_file(),
		 * else disabled.
		 */
	#endif
	#endif

		int ka_time;
		/**< CONTEXT: 0 for no TCP keepalive, otherwise apply this keepalive
		 * timeout to all libwebsocket sockets, client or server */
		int ka_probes;
		/**< CONTEXT: if ka_time was nonzero, after the timeout expires how many
		 * times to try to get a response from the peer before giving up
		 * and killing the connection */
		int ka_interval;
		/**< CONTEXT: if ka_time was nonzero, how long to wait before each ka_probes
		 * attempt */
		unsigned int timeout_secs;
		/**< VHOST: various processes involving network roundtrips in the
		 * library are protected from hanging forever by timeouts.  If
		 * nonzero, this member lets you set the timeout used in seconds.
		 * Otherwise a default timeout is used. */
		unsigned int connect_timeout_secs;
		/**< VHOST: client connections have this long to find a working server
		 * from the DNS results, or the whole connection times out.  If zero,
		 * a default timeout is used */
		int bind_iface;
		/**< VHOST: nonzero to strictly bind sockets to the interface name in
		 * .iface (eg, "eth2"), using SO_BIND_TO_DEVICE.
		 *
		 * Requires SO_BINDTODEVICE support from your OS and CAP_NET_RAW
		 * capability.
		 *
		 * Notice that common things like access network interface IP from
		 * your local machine use your lo / loopback interface and will be
		 * disallowed by this.
		 */
		unsigned int timeout_secs_ah_idle;
		/**< VHOST: seconds to allow a client to hold an ah without using it.
		 * 0 defaults to 10s. */
	#endif /* WITH_NETWORK */

	#if defined(LWS_WITH_TLS_SESSIONS)
		uint32_t			tls_session_timeout;
		/**< VHOST: seconds until timeout/ttl for newly created sessions.
		 * 0 means default timeout (defined per protocol, usually 300s). */
		uint32_t			tls_session_cache_max;
		/**< VHOST: 0 for default limit of 10, or the maximum number of
		 * client tls sessions we are willing to cache */
	#endif

		gid_t gid;
		/**< CONTEXT: group id to change to after setting listen socket,
		 *   or -1. See also .username below. */
		uid_t uid;
		/**< CONTEXT: user id to change to after setting listen socket,
		 *   or -1.  See also .groupname below. */
		uint64_t options;
		/**< VHOST + CONTEXT: 0, or LWS_SERVER_OPTION_... bitfields */
		void *user;
		/**< VHOST + CONTEXT: optional user pointer that will be associated
		 * with the context when creating the context (and can be retrieved by
		 * lws_context_user(context), or with the vhost when creating the vhost
		 * (and can be retrieved by lws_vhost_user(vhost)).  You will need to
		 * use LWS_SERVER_OPTION_EXPLICIT_VHOSTS and create the vhost separately
		 * if you care about giving the context and vhost different user pointer
		 * values.
		 */
		unsigned int count_threads;
		/**< CONTEXT: how many contexts to create in an array, 0 = 1 */
		unsigned int fd_limit_per_thread;
		/**< CONTEXT: nonzero means restrict each service thread to this
		 * many fds, 0 means the default which is divide the process fd
		 * limit by the number of threads.
		 *
		 * Note if this is nonzero, and fd_limit_per_thread multiplied by the
		 * number of service threads is less than the process ulimit, then lws
		 * restricts internal lookup table allocation to the smaller size, and
		 * switches to a less efficient lookup scheme.  You should use this to
		 * trade off speed against memory usage if you know the lws context
		 * will only use a handful of fds.
		 *
		 * Bear in mind lws may use some fds internally, for example for the
		 * cancel pipe, so you may need to allow for some extras for normal
		 * operation.
		 */
		const char *vhost_name;
		/**< VHOST: name of vhost, must match external DNS name used to
		 * access the site, like "warmcat.com" as it's used to match
		 * Host: header and / or SNI name for SSL.
		 * CONTEXT: NULL, or the name to associate with the context for
		 * context-specific logging
		 */
	#if defined(LWS_WITH_PLUGINS)
		const char * const *plugin_dirs;
		/**< CONTEXT: NULL, or NULL-terminated array of directories to
		 * scan for lws protocol plugins at context creation time */
	#endif
		void *external_baggage_free_on_destroy;
		/**< CONTEXT: NULL, or pointer to something externally malloc'd, that
		 * should be freed when the context is destroyed.  This allows you to
		 * automatically sync the freeing action to the context destruction
		 * action, so there is no need for an external free() if the context
		 * succeeded to create.
		 */


		unsigned int pt_serv_buf_size;
		/**< CONTEXT: 0 = default of 4096.  This buffer is used by
		 * various service related features including file serving, it
		 * defines the max chunk of file that can be sent at once.
		 * At the risk of lws having to buffer failed large sends, it
		 * can be increased to, eg, 128KiB to improve throughput. */
	#if defined(LWS_WITH_FILE_OPS)
		const struct lws_plat_file_ops *fops;
		/**< CONTEXT: NULL, or pointer to an array of fops structs, terminated
		 * by a sentinel with NULL .open.
		 *
		 * If NULL, lws provides just the platform file operations struct for
		 * backwards compatibility.
		 */
	#endif

	#if defined(LWS_WITH_SOCKS5)
		const char *socks_proxy_address;
		/**< VHOST: If non-NULL, attempts to proxy via the given address.
		 * If proxy auth is required, use format
		 * "username:password\@server:port" */
		unsigned int socks_proxy_port;
		/**< VHOST: If socks_proxy_address was non-NULL, uses this port
		 * if nonzero, otherwise requires "server:port" in .socks_proxy_address
		 */
	#endif

	#if defined(LWS_HAVE_SYS_CAPABILITY_H) && defined(LWS_HAVE_LIBCAP)
		cap_value_t caps[4];
		/**< CONTEXT: array holding Linux capabilities you want to
		 * continue to be available to the server after it transitions
		 * to a noprivileged user.  Usually none are needed but for, eg,
		 * .bind_iface, CAP_NET_RAW is required.  This gives you a way
		 * to still have the capability but drop root.
		 */
		char count_caps;
		/**< CONTEXT: count of Linux capabilities in .caps[].  0 means
		 * no capabilities will be inherited from root (the default) */
	#endif
		void **foreign_loops;
		/**< CONTEXT: This is ignored if the context is not being started with
		 *		an event loop, ie, .options has a flag like
		 *		LWS_SERVER_OPTION_LIBUV.
		 *
		 *		NULL indicates lws should start its own even loop for
		 *		each service thread, and deal with closing the loops
		 *		when the context is destroyed.
		 *
		 *		Non-NULL means it points to an array of external
		 *		("foreign") event loops that are to be used in turn for
		 *		each service thread.  In the default case of 1 service
		 *		thread, it can just point to one foreign event loop.
		 */
		void (*signal_cb)(void *event_lib_handle, int signum);
		/**< CONTEXT: NULL: default signal handling.  Otherwise this receives
		 *		the signal handler callback.  event_lib_handle is the
		 *		native event library signal handle, eg uv_signal_t *
		 *		for libuv.
		 */
		struct lws_context **pcontext;
		/**< CONTEXT: if non-NULL, at the end of context destroy processing,
		 * the pointer pointed to by pcontext is written with NULL.  You can
		 * use this to let foreign event loops know that lws context destruction
		 * is fully completed.
		 */
		void (*finalize)(struct lws_vhost *vh, void *arg);
		/**< VHOST: NULL, or pointer to function that will be called back
		 *	    when the vhost is just about to be freed.  The arg parameter
		 *	    will be set to whatever finalize_arg is below.
		 */
		void *finalize_arg;
		/**< VHOST: opaque pointer lws ignores but passes to the finalize
		 *	    callback.  If you don't care, leave it NULL.
		 */
		const char *listen_accept_role;
		/**< VHOST: NULL for default, or force accepted incoming connections to
		 * bind to this role.  Uses the role names from their ops struct, eg,
		 * "raw-skt".
		 */
		const char *listen_accept_protocol;
		/**< VHOST: NULL for default, or force accepted incoming connections to
		 * bind to this vhost protocol name.
		 */
		const struct lws_protocols **pprotocols;
		/**< VHOST: NULL: use .protocols, otherwise ignore .protocols and use
		 * this array of pointers to protocols structs.  The end of the array
		 * is marked by a NULL pointer.
		 *
		 * This is preferred over .protocols, because it allows the protocol
		 * struct to be opaquely defined elsewhere, with just a pointer to it
		 * needed to create the context with it.  .protocols requires also
		 * the type of the user data to be known so its size can be given.
		 */

		const char *username; /**< CONTEXT: string username for post-init
		 * permissions.  Like .uid but takes a string username. */
		const char *groupname; /**< CONTEXT: string groupname for post-init
		 * permissions.  Like .gid but takes a string groupname. */
		const char *unix_socket_perms; /**< VHOST: if your vhost is listening
		 * on a unix socket, you can give a "username:groupname" string here
		 * to control the owner:group it's created with.  It's always created
		 * with 0660 mode. */
		const lws_system_ops_t *system_ops;
		/**< CONTEXT: hook up lws_system_ apis to system-specific
		 * implementations */
		const lws_retry_bo_t *retry_and_idle_policy;
		/**< VHOST: optional retry and idle policy to apply to this vhost.
		 *   Currently only the idle parts are applied to the connections.
		 */
	#if defined(LWS_WITH_SYS_STATE)
		lws_state_notify_link_t * const *register_notifier_list;
		/**< CONTEXT: NULL, or pointer to an array of notifiers that should
		 * be registered during context creation, so they can see state change
		 * events from very early on.  The array should end with a NULL. */
	#endif
	#if defined(LWS_WITH_SECURE_STREAMS)
	#if defined(LWS_WITH_SECURE_STREAMS_STATIC_POLICY_ONLY)
		const struct lws_ss_policy *pss_policies; /**< CONTEXT: point to first
		 * in a linked-list of streamtype policies prepared by user code */
	#else
		const char *pss_policies_json; /**< CONTEXT: point to a string
		 * containing a JSON description of the secure streams policies.  Set
		 * to NULL if not using Secure Streams.
		 * If the platform supports files and the string does not begin with
		 * '{', lws treats the string as a filepath to open to get the JSON
		 * policy.
		 */
	#endif
		const struct lws_ss_plugin **pss_plugins; /**< CONTEXT: point to an array
		 * of pointers to plugin structs here, terminated with a NULL ptr.
		 * Set to NULL if not using Secure Streams. */
		const char *ss_proxy_bind; /**< CONTEXT: NULL, or: ss_proxy_port == 0:
		 * point to a string giving the Unix Domain Socket address to use (start
		 * with @ for abstract namespace), ss_proxy_port nonzero: set the
		 * network interface address (not name, it's ambiguous for ipv4/6) to
		 * bind the tcp connection to the proxy to */
		const char *ss_proxy_address; /**< CONTEXT: NULL, or if ss_proxy_port
		 * nonzero: the tcp address of the ss proxy to connect to */
		uint16_t ss_proxy_port; /* 0 = if connecting to ss proxy, do it via a
		 * Unix Domain Socket, "+@proxy.ss.lws" if ss_proxy_bind is NULL else
		 * the socket path given in ss_proxy_bind (start it with a + or +@);
		 * nonzero means connect via a tcp socket to the tcp address in
		 * ss_proxy_bind and the given port */
		const struct lws_transport_proxy_ops *txp_ops_ssproxy; /**< CONTEXT: NULL, or
		 * custom sss transport ops used for ss proxy communication.  NULL means
		 * to use the default wsi-based proxy server */
		const void *txp_ssproxy_info; /**< CONTEXT: NULL, or extra transport-
		 * specifi creation info to be used at \p txp_ops_ssproxy creation */
		const struct lws_transport_client_ops *txp_ops_sspc; /**< CONTEXT: NULL, or
		 * custom sss transport ops used for ss client communication to the ss
		 * proxy.  NULL means to use the default wsi-based client support */
	#endif

	#if defined(LWS_WITH_SECURE_STREAMS_PROXY_API)
	#endif

		int rlimit_nofile;
		/**< 0 = inherit the initial ulimit for files / sockets from the startup
		 * environment.  Nonzero = try to set the limit for this process.
		 */
	#if defined(LWS_WITH_PEER_LIMITS)
		lws_peer_limits_notify_t pl_notify_cb;
		/**< CONTEXT: NULL, or a callback to receive notifications each time a
		 * connection is being dropped because of peer limits.
		 *
		 * The callback provides the context, and an lws_sockaddr46 with the
		 * peer address and port.
		 */
		unsigned short ip_limit_ah;
		/**< CONTEXT: max number of ah a single IP may use simultaneously
		 *	      0 is no limit. This is a soft limit: if the limit is
		 *	      reached, connections from that IP will wait in the ah
		 *	      waiting list and not be able to acquire an ah until
		 *	      a connection belonging to the IP relinquishes one it
		 *	      already has.
		 */
		unsigned short ip_limit_wsi;
		/**< CONTEXT: max number of wsi a single IP may use simultaneously.
		 *	      0 is no limit.  This is a hard limit, connections from
		 *	      the same IP will simply be dropped once it acquires the
		 *	      amount of simultaneous wsi / accepted connections
		 *	      given here.
		 */

	#endif /* PEER_LIMITS */

	#if defined(LWS_WITH_SYS_FAULT_INJECTION)
		lws_fi_ctx_t				fic;
		/**< CONTEXT | VHOST: attach external Fault Injection context to the
		 * lws_context or vhost.  If creating the context + default vhost in
		 * one step, only the context binds to \p fi.  When creating a vhost
		 * otherwise this can bind to the vhost so the faults can be injected
		 * from the start.
		 */
	#endif

	#if defined(LWS_WITH_SYS_SMD)
		lws_smd_notification_cb_t		early_smd_cb;
		/**< CONTEXT: NULL, or an smd notification callback that will be registered
		 * immediately after the smd in the context is initialized.  This ensures
		 * you can get all notifications without having to intercept the event loop
		 * creation, eg, when using an event library.  Other callbacks can be
		 * registered later manually without problems.
		 */
		void					*early_smd_opaque;
		lws_smd_class_t				early_smd_class_filter;
		lws_usec_t				smd_ttl_us;
		/**< CONTEXT: SMD messages older than this many us are removed from the
		 * queue and destroyed even if not fully delivered yet.  If zero,
		 * defaults to 2 seconds (5 second for FREERTOS).
		 */
		uint16_t				smd_queue_depth;
		/**< CONTEXT: Maximum queue depth, If zero defaults to 40
		 * (20 for FREERTOS) */
	#endif

	#if defined(LWS_WITH_SYS_METRICS)
		const struct lws_metric_policy		*metrics_policies;
		/**< CONTEXT: non-SS policy metrics policies */
		const char				*metrics_prefix;
		/**< CONTEXT: prefix for this context's metrics, used to distinguish
		 * metrics pooled from different processes / applications, so, eg what
		 * would be "cpu.svc" if this is NULL becomes "myapp.cpu.svc" is this is
		 * set to "myapp".  Policies are applied using the name with the prefix,
		 * if present.
		 */
	#endif

		int					fo_listen_queue;
		/**< VHOST: 0 = no TCP_FASTOPEN, nonzero = enable TCP_FASTOPEN if the
		 * platform supports it, with the given queue length for the listen
		 * socket.
		 */

		const struct lws_plugin_evlib		*event_lib_custom;
		/**< CONTEXT: If non-NULL, override event library selection so it uses
		 * this custom event library implementation, instead of default internal
		 * loop.  Don't set any other event lib context creation flags in that
		 * case. it will be used automatically.  This is useful for integration
		 * where an existing application is using its own handrolled event loop
		 * instead of an event library, it provides a way to allow lws to use
		 * the custom event loop natively as if it were an "event library".
		 */

	#if defined(LWS_WITH_TLS_JIT_TRUST)
		size_t					jitt_cache_max_footprint;
		/**< CONTEXT: 0 for no limit, else max bytes used by JIT Trust cache...
		 * LRU items are evicted to keep under this limit */
		int					vh_idle_grace_ms;
		/**< CONTEXT: 0 for default of 5000ms, or number of ms JIT Trust vhosts
		 * are allowed to live without active connections using them. */
	#endif

		lws_log_cx_t				*log_cx;
		/**< CONTEXT: NULL to use the default, process-scope logging context,
		 * else a specific logging context to associate with this context */

	#if defined(LWS_WITH_CACHE_NSCOOKIEJAR) && defined(LWS_WITH_CLIENT)
		const char				*http_nsc_filepath;
		/**< CONTEXT: Filepath to use for http netscape cookiejar file */

		size_t					http_nsc_heap_max_footprint;
		/**< CONTEXT: 0, or limit in bytes for heap usage of memory cookie
		 * cache */
		size_t					http_nsc_heap_max_items;
		/**< CONTEXT: 0, or the max number of items allowed in the cookie cache
		 * before destroying lru items to keep it under the limit */
		size_t					http_nsc_heap_max_payload;
		/**< CONTEXT: 0, or the maximum size of a single cookie we are able to
		 * handle */
	#endif

	#if defined(LWS_WITH_SYS_ASYNC_DNS)
		const char				**async_dns_servers;
		/**< CONTEXT: NULL, or a pointer to an array of strings containing the
		 * numeric IP like "8.8.8.8" or "2001:4860:4860::8888" for a list of DNS
		 * server to forcibly add.  If given, the list of strings must be
		 * terminated with a NULL.
		 */
	#endif

		/* Add new things just above here ---^
		 * This is part of the ABI, don't needlessly break compatibility
		 *
		 * The below is to ensure later library versions with new
		 * members added above will see 0 (default) even if the app
		 * was not built against the newer headers.
		 */

		void *_unused[2]; /**< dummy */
	};