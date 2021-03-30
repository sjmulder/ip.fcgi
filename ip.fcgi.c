#include <sys/types.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <err.h>
#include <kcgi.h>

static void
handle(struct kreq *req)
{
	khttp_head(req, kresps[KRESP_STATUS], "%s", khttps[KHTTP_200]);
	khttp_head(req, kresps[KRESP_CONTENT_TYPE], "%s",
	    kmimetypes[KMIME_TEXT_PLAIN]);
	khttp_body(req);
	khttp_puts(req, req->remote);
	khttp_puts(req, "\n");
}

int
main(void)
{
	struct kfcgi *fcgi;
	struct kreq req;
	enum kcgi_err err;

	err = khttp_fcgi_init(&fcgi, NULL, 0, NULL, 0, 0);
	if (err != KCGI_OK)
		errx(1, "khttp_fcgi_init: error %d", err);

	while ((err = khttp_fcgi_parse(fcgi, &req)) == KCGI_OK) {
		handle(&req);
		khttp_free(&req);
	}

	if (err != KCGI_EXIT)
		errx(1, "khttp_fcgi_parse: error %d", err);

	khttp_fcgi_free(fcgi);
	return 0;
}
