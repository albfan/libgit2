#include "diff_parse.h"
#define parse_advance_expected_str(ctx, str) \
	parse_advance_expected(ctx, str, strlen(str))
		return parse_err("invalid file mode at line %"PRIuZ, ctx->line_num);
	uint16_t *oid_len,
	if (len < GIT_OID_MINPREFIXLEN || len > GIT_OID_HEXSZ ||
		return parse_err("invalid hex formatted object id at line %"PRIuZ,
	*oid_len = (uint16_t)len;
		parse_advance_expected_str(ctx, "..") < 0 ||
	if (parse_advance_expected_str(ctx, "%") < 0)
		return parse_err("invalid similarity percentage at line %"PRIuZ,
		return parse_err("invalid similarity percentage at line %"PRIuZ,
	{ "Binary files ", NULL },
	if (parse_advance_expected_str(ctx, "diff --git ") < 0)
		return parse_err("corrupt git diff header at line %"PRIuZ, ctx->line_num);
		return parse_err("corrupt old path in git diff header at line %"PRIuZ,
		return parse_err("corrupt new path in git diff header at line %"PRIuZ,
			parse_advance_expected_str(ctx, "\n");
				error = parse_err("trailing data at line %"PRIuZ, ctx->line_num);
			error = parse_err("invalid patch header at line %"PRIuZ,
	if (parse_advance_expected_str(ctx, "@@ -") < 0 ||
		if (parse_advance_expected_str(ctx, ",") < 0 ||
	if (parse_advance_expected_str(ctx, " +") < 0 ||
		if (parse_advance_expected_str(ctx, ",") < 0 ||
	if (parse_advance_expected_str(ctx, " @@") < 0)
		return parse_err("oversized patch hunk header at line %"PRIuZ,
	giterr_set(GITERR_PATCH, "invalid patch hunk header at line %"PRIuZ,
			error = parse_err("invalid patch instruction at line %"PRIuZ,
			error = parse_err("invalid patch hunk at line %"PRIuZ, ctx->line_num);
			error = parse_err("invalid hunk header outside patch at line %"PRIuZ,
			"unknown binary delta type at line %"PRIuZ, ctx->line_num);
		error = parse_err("invalid binary size at line %"PRIuZ, ctx->line_num);
			error = parse_err("invalid binary length at line %"PRIuZ, ctx->line_num);
			error = parse_err("truncated binary data at line %"PRIuZ, ctx->line_num);
			error = parse_err("truncated binary data at line %"PRIuZ, ctx->line_num);
			error = parse_err("trailing data at line %"PRIuZ, ctx->line_num);
	if (parse_advance_expected_str(ctx, "GIT binary patch") < 0 ||
		return parse_err("corrupt git binary header at line %"PRIuZ, ctx->line_num);
		return parse_err("corrupt git binary separator at line %"PRIuZ,
		return parse_err("corrupt git binary patch separator at line %"PRIuZ,
	patch->base.binary.contains_data = 1;
	patch->base.delta->flags |= GIT_DIFF_FLAG_BINARY;
	return 0;
}

static int parse_patch_binary_nodata(
	git_patch_parsed *patch,
	git_patch_parse_ctx *ctx)
{
	if (parse_advance_expected_str(ctx, "Binary files ") < 0 ||
		parse_advance_expected_str(ctx, patch->header_old_path) < 0 ||
		parse_advance_expected_str(ctx, " and ") < 0 ||
		parse_advance_expected_str(ctx, patch->header_new_path) < 0 ||
		parse_advance_expected_str(ctx, " differ") < 0 ||
		parse_advance_nl(ctx) < 0)
		return parse_err("corrupt git binary header at line %"PRIuZ, ctx->line_num);

	patch->base.binary.contains_data = 0;
	else if (parse_ctx_contains_s(ctx, "Binary files "))
		return parse_patch_binary_nodata(patch, ctx);
			"header filename does not contain %"PRIuZ" path components",
		if ((ctx->content = git__malloc(content_len)) == NULL) {
			git__free(ctx);
		}
int git_patch_parsed_from_diff(git_patch **out, git_diff *d, size_t idx)
{
	git_diff_parsed *diff = (git_diff_parsed *)d;
	git_patch *p;

	if ((p = git_vector_get(&diff->patches, idx)) == NULL)
		return -1;

	GIT_REFCOUNT_INC(p);
	*out = p;

	return 0;
}
